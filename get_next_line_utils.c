/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkieszek <pkieszek@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 02:34:01 by pkieszek          #+#    #+#             */
/*   Updated: 2025/02/19 17:10:23 by pkieszek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 * Returns the length of a string.
 * Ensures safe access to the pointer before iteration.
 */
size_t ft_strlen(const char *s)
{
    size_t len = 0;
    while (s && s[len])
        len++;
    return (len);
}

/*
 * Finds the first occurrence of a character in a string.
 * Ensures that `s` is not NULL before accessing it.
 */
char *ft_strchr(const char *s, int c)
{
    if (!s)
        return (NULL);
    while (*s)
    {
        if (*s == (char)c)
            return ((char *)s);
        s++;
    }
    return (NULL);
}

/*
 * Concatenates two strings into a new buffer.
 * Ensures safe memory allocation and avoids buffer overflow.
 */
char *ft_strjoin(char *s1, char *s2)
{
    size_t len1 = s1 ? ft_strlen(s1) : 0;
    size_t len2 = s2 ? ft_strlen(s2) : 0;
    char *new_str = (char *)malloc(len1 + len2 + 1);

    if (!new_str)
        return (NULL);
    
    size_t i = 0;
    if (s1)
    {
        while (s1[i])
        {
            new_str[i] = s1[i];
            i++;
        }
        free(s1); // Free old buffer to prevent memory leaks
    }
    
    size_t j = 0;
    while (s2 && s2[j])
        new_str[i++] = s2[j++];
    
    new_str[i] = '\0';
    return (new_str);
}

/*
 * Duplicates a string safely.
 * Ensures the allocated memory is properly copied and null-terminated.
 */
char *ft_strdup(const char *s)
{
    size_t len = ft_strlen(s);
    char *dup = (char *)malloc(len + 1);

    if (!dup)
        return (NULL);
    
    ft_strlcpy(dup, s, len + 1);
    return (dup);
}

/*
 * Copies a string with a size limit.
 * Ensures buffer safety by properly null-terminating the destination.
 */
size_t ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
    size_t i = 0;

    if (!dst || !src)
        return (0);
    
    while (i + 1 < dstsize && src[i])
    {
        dst[i] = src[i];
        i++;
    }
    
    if (dstsize > 0)
        dst[i] = '\0';
    
    return (ft_strlen(src));
}