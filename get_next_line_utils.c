/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkieszek <pkieszek@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 02:34:01 by pkieszek          #+#    #+#             */
/*   Updated: 2025/02/19 23:34:58 by pkieszek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 * Calculates the length of a string.
 * Iterates through the string until it reaches the null terminator.
 * Returns the total length of the string.
 */
ssize_t	str_len(const char *s)
{
	ssize_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*
 * Allocates memory for an empty string.
 * The function ensures that `str` is assigned to a valid memory block.
 * Returns 1 on success, and 0 if memory allocation fails.
 */
int	create_empty_line(char **str)
{
	*str = malloc(1);
	if (!*str)
		return (0);
	(*str)[0] = '\0';
	return (1);
}

/*
 * Finds the position of the first newline character ('\n') in a buffer.
 * Iterates through the buffer and returns the position index +1 if found.
 * If no newline is found, returns 0.
 */
ssize_t	find_newline(char *buf, ssize_t i)
{
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}
