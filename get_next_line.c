/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkieszek <pkieszek@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 02:33:42 by pkieszek          #+#    #+#             */
/*   Updated: 2025/02/20 00:00:54 by pkieszek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* 
	read_buffer:
	- Reads a chunk of data from the file into the buffer (temporary storage).
	- If the read operation reaches the end of the file (EOF) 
	  or encounters an error, it frees the stored text and returns 0.
	- Otherwise, it null-terminates the buffer and returns 1 to indicate success.
*/
static int	read_buffer(int file_descriptor, char **saved_text, char *buffer)
{
	ssize_t	bytes_read;

	bytes_read = read(file_descriptor, buffer, BUFFER_SIZE);
	if (bytes_read == 0 && (**saved_text))
		return (0);
	if (bytes_read <= 0)
	{
		free(*saved_text);
		*saved_text = NULL;
		return (0);
	}
	buffer[bytes_read] = '\0';
	return (1);
}

/* 
	allocate_text:
	- Creates a new string by combining:
	  (1) the existing stored text
	  (2) a portion of the buffer starting at 'start_position' 
	      with 'length' characters
	- If memory allocation fails, the existing text is freed, 
	  and NULL is returned.
*/
static char	*allocate_text(char *previous_text, char *buffer,
				ssize_t start_position, ssize_t length)
{
	ssize_t	i;
	char	*new_text;

	new_text = (char *)malloc(sizeof(char)
			* (str_len(previous_text) + length + 1));
	if (!new_text)
	{
		free(previous_text);
		return (NULL);
	}
	i = 0;
	while (previous_text[i])
	{
		new_text[i] = previous_text[i];
		i++;
	}
	free(previous_text);
	new_text[i + length] = '\0';
	while (length)
	{
		length--;
		new_text[i + length] = buffer[start_position + length];
	}
	return (new_text);
}

/* 
	add_to_stored_text:
	- Appends a new portion of the buffer to the stored text.
	- If allocation fails, returns 0 (error).
	- Otherwise, resets the position and length, then returns 1 (success).
*/
static int	add_to_stored_text(char **stored_text, char *buffer,
				ssize_t *position_in_buffer, ssize_t *line_length)
{
	*stored_text = allocate_text(*stored_text, buffer, *position_in_buffer,
			BUFFER_SIZE - *position_in_buffer);
	if (!*stored_text)
		return (0);
	*position_in_buffer = 0;
	*line_length = 0;
	return (1);
}

/* 
	extract_complete_line:
	- Extracts the portion of the buffer containing a full line 
	  and adds it to 'line'.
	- Updates position_in_buffer to point after the newline.
*/
static char	*extract_complete_line(char *line, char *buffer,
				ssize_t *position_in_buffer, ssize_t *line_length)
{
	line = allocate_text(line, buffer, *position_in_buffer, *line_length);
	*position_in_buffer += *line_length;
	*line_length = 0;
	return (line);
}

/* 
	get_next_line:
	- Reads from the file line by line.
	- Uses a static buffer to store data across function calls.
	- Keeps track of where it left off in the buffer.
	- Returns a single line each time it is called.
*/
char	*get_next_line(int file_descriptor)
{
	char			*complete_line_text;
	static char		buffer[BUFFER_SIZE + 1];
	static ssize_t	position_in_buffer = 0;
	static ssize_t	line_length = 0;

	if (file_descriptor < 0 || BUFFER_SIZE <= 0
		|| !create_empty_line(&complete_line_text))
		return (NULL);
	while (!line_length)
	{
		if (!position_in_buffer && !read_buffer(file_descriptor,
				&complete_line_text, buffer))
			return (complete_line_text);
		line_length = find_newline(buffer, position_in_buffer)
			- position_in_buffer;
		if (line_length > 0)
			return (extract_complete_line(complete_line_text, buffer,
					&position_in_buffer, &line_length));
		else if (!add_to_stored_text(&complete_line_text, buffer,
				&position_in_buffer, &line_length))
			return (NULL);
	}
	return (NULL);
}
