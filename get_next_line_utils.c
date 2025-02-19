/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkieszek <pkieszek@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 02:34:01 by pkieszek          #+#    #+#             */
/*   Updated: 2025/02/19 16:22:01 by pkieszek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t ft_strlen(const char *s)
{
    size_t len = 0;
    while (s && s[len])
        len++;
    return (len);
}

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

char *ft_strjoin(char *s1, char *s2)
{
    size_t len1 = ft_strlen(s1);
    size_t len2 = ft_strlen(s2);
    char *new_str = (char *)malloc(len1 + len2 + 1);
    size_t i = 0, j = 0;

    if (!new_str)
        return (NULL);
    if (s1)
    {
        while (s1[i])
            new_str[i] = s1[i++];
        free(s1);
    }
    while (s2[j])
        new_str[i++] = s2[j++];
    new_str[i] = '\0';
    return (new_str);
}

char *ft_strdup(const char *s)
{
    size_t len = ft_strlen(s);
    char *dup = (char *)malloc(len + 1);
    size_t i = 0;

    if (!dup)
        return (NULL);
    while (s[i])
    {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}

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
