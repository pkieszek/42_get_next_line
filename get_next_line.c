/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkieszek <pkieszek@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 02:33:42 by pkieszek          #+#    #+#             */
/*   Updated: 2025/02/19 22:45:32 by pkieszek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Reads and appends data to the buffer safely */
static int read_and_store(int fd, char **buffer)
{
    char temp_buffer[BUFFER_SIZE + 1];
    ssize_t bytes_read;
    char *new_buffer;

    if (!buffer || fd < 0 || BUFFER_SIZE <= 0)
        return (0);

    bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
    if (bytes_read <= 0)
        return (0);
    
    temp_buffer[bytes_read] = '\0';
    new_buffer = ft_strjoin(*buffer, temp_buffer);
    free(*buffer);
    *buffer = new_buffer;
    return (*buffer != NULL);
}

/* Extracts a single line from buffer */
static char *extract_line(char *buffer)
{
    size_t len = 0;
    char *line;
    
    if (!buffer || buffer[0] == '\0')
        return (NULL);
    
    while (buffer[len] && buffer[len] != '\n')
        len++;
    
    line = (char *)malloc(len + (buffer[len] == '\n' ? 2 : 1));
    if (!line)
        return (NULL);
    
    ft_strlcpy(line, buffer, len + (buffer[len] == '\n' ? 2 : 1));
    return (line);
}

/* Trims the buffer after extracting a line */
static void trim_buffer(char **buffer)
{
    char *new_buffer;
    char *newline_pos;

    if (!*buffer)
        return;
    
    newline_pos = ft_strchr(*buffer, '\n');
    if (!newline_pos)
    {
        free(*buffer);
        *buffer = NULL;
        return;
    }
    
    new_buffer = ft_strdup(newline_pos + 1);
    free(*buffer);
    *buffer = new_buffer;
}

/* Main function to get the next line */
char *get_next_line(int fd)
{
    static char *buffer = NULL;
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    
    if (!read_and_store(fd, &buffer))
    {
        free(buffer);
        buffer = NULL;
        return (NULL);
    }
    
    line = extract_line(buffer);
    trim_buffer(&buffer);
    return (line);
}
