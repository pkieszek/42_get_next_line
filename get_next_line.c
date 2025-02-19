/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkieszek <pkieszek@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 02:33:42 by pkieszek          #+#    #+#             */
/*   Updated: 2025/02/19 16:10:49 by pkieszek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Reads from the file descriptor and updates the buffer */
static char	*read_and_store(int fd, char *buffer)
{
	char	temp_buffer[BUFFER_SIZE + 1];
	ssize_t	bytes_read;

	bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (NULL);
	temp_buffer[bytes_read] = '\0';
	return (ft_strjoin(buffer, temp_buffer));
}

/* Extracts a line from the buffer */
static char	*extract_line(char *buffer)
{
	char	*line;
	size_t	len;

	len = 0;
	while (buffer[len] && buffer[len] != '\n')
		len++;
	line = (char *)malloc(len + 2);
	if (!line)
		return (NULL);
	ft_strlcpy(line, buffer, len + 2);
	return (line);
}

/* Updates buffer to remove the extracted line */
static char	*trim_buffer(char *buffer)
{
	char	*new_buffer;
	char	*newline_pos;

	newline_pos = ft_strchr(buffer, '\n');
	if (!newline_pos)
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = ft_strdup(newline_pos + 1);
	free(buffer);
	return (new_buffer);
}

/* Main function to return the next line from fd */
char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_and_store(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	buffer = trim_buffer(buffer);
	return (line);
}
