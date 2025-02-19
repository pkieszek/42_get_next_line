/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkieszek <pkieszek@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 02:33:42 by pkieszek          #+#    #+#             */
/*   Updated: 2025/02/19 23:53:54 by pkieszek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* 
	read_buf:
	- Reads a chunk of data from the file descriptor (fd) into the buffer (buf).
	- If the read operation reaches the end of the file (EOF) 
	  or encounters an error, it frees the stored string (*str) and returns 0.
	- Otherwise, it null-terminates the buffer and returns 1 to indicate success.
*/
static int	read_buf(int fd, char **str, char *buf)
{
	ssize_t	bytes_read;

	bytes_read = read(fd, buf, BUFFER_SIZE);
	if (bytes_read == 0 && (**str))
		return (0);
	if (bytes_read <= 0)
	{
		free(*str);
		*str = NULL;
		return (0);
	}
	buf[bytes_read] = '\0';
	return (1);
}

/* 
	alloc_str:
	- Allocates memory for a new string that contains:
	  (1) the existing content of old_chunk_str
	  (2) a portion of buf starting from 'start' with a length of 'len'
	- If memory allocation fails, old_chunk_str is freed and NULL is returned.
*/
static char	*alloc_str(char *old_chunk_str, char *buf, ssize_t start,
				ssize_t len)
{
	ssize_t	i;
	char	*new_str;

	new_str = (char *)malloc(sizeof(char)
			* (str_len(old_chunk_str) + len + 1));
	if (!new_str)
	{
		free(old_chunk_str);
		return (NULL);
	}
	i = 0;
	while (old_chunk_str[i])
	{
		new_str[i] = old_chunk_str[i];
		i++;
	}
	free(old_chunk_str);
	new_str[i + len] = '\0';
	while (len)
	{
		len--;
		new_str[i + len] = buf[start + len];
	}
	return (new_str);
}

/* 
	add_chunk:
	- Appends a new portion of the buffer to chunk_str.
	- If allocation fails, returns 0 (error).
	- Otherwise, resets line_start and line_len, then returns 1 (success).
*/
static int	add_chunk(char **chunk_str, char *buf, ssize_t *line_start,
		ssize_t *line_len)
{
	*chunk_str = alloc_str(*chunk_str, buf, *line_start,
			BUFFER_SIZE - *line_start);
	if (!*chunk_str)
		return (0);
	*line_start = 0;
	*line_len = 0;
	return (1);
}

/* 
	complete_line:
	- Adds the portion of the buffer containing a full line to 'line'.
	- Updates line_start to the position after the newline.
*/
static char	*complete_line(char *line, char *buf, ssize_t *line_start,
		ssize_t *line_len)
{
	line = alloc_str(line, buf, *line_start, *line_len);
	*line_start += *line_len;
	*line_len = 0;
	return (line);
}

/* 
	get_next_line:
	- Reads from the file descriptor (fd) line by line.
	- Uses a static buffer to store data across function calls.
	- Keeps track of where it left off with line_start.
	- Returns a single line each time it is called.
*/
char	*get_next_line(int fd)
{
	char			*full_line;
	static char		buf[BUFFER_SIZE + 1];
	static ssize_t	line_start = 0;
	static ssize_t	len = 0;

	if (fd < 0 || BUFFER_SIZE <= 0 || !create_empty_line(&full_line))
		return (NULL);
	while (!len)
	{
		if (!line_start && !read_buf(fd, &full_line, buf))
			return (full_line);
		len = find_newline(buf, line_start) - line_start;
		if (len > 0)
			return (complete_line(full_line, buf, &line_start, &len));
		else if (!add_chunk(&full_line, buf, &line_start, &len))
			return (NULL);
	}
	return (NULL);
}
