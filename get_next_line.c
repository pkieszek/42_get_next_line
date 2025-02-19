/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkieszek <pkieszek@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 02:33:42 by pkieszek          #+#    #+#             */
/*   Updated: 2025/02/19 17:09:06 by pkieszek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 * Reads from the file descriptor and appends the data to the buffer.
 * Ensures memory safety and avoids buffer overflows.
 */
static char *read_and_store(int fd, char *buffer)
{
    char temp_buffer[BUFFER_SIZE + 1];
    ssize_t bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
        return (NULL);
    
    bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
    if (bytes_read <= 0)
        return (NULL);
    
    temp_buffer[bytes_read] = '\0';
    return (ft_strjoin(buffer, temp_buffer));
}

/*
 * Extracts a single line from the buffer safely.
 * Ensures allocated memory is initialized properly.
 */
static char *extract_line(char *buffer)
{
    char *line;
    size_t len = 0;

    if (!buffer || buffer[0] == '\0')
        return (NULL);
    
    while (buffer[len] && buffer[len] != '\n')
        len++;
    
    line = (char *)malloc(len + 2);
    if (!line)
        return (NULL);
    
    ft_strlcpy(line, buffer, len + 2);
    return (line);
}

/*
 * Trims the buffer by removing the extracted line.
 * Ensures that old buffer memory is freed properly.
 */
static char *trim_buffer(char *buffer)
{
    char *new_buffer;
    char *newline_pos;

    if (!buffer)
        return (NULL);
    
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

/*
 * The main function to retrieve the next line from the file descriptor.
 * Manages a static buffer to store remaining data.
 */
char *get_next_line(int fd)
{
    static char *buffer;
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
        return (NULL);
    
    buffer = read_and_store(fd, buffer);
    if (!buffer)
        return (NULL);
    
    line = extract_line(buffer);
    buffer = trim_buffer(buffer);
    return (line);
}
