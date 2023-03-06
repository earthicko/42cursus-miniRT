/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtools2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:43:49 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:50 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*cursor;

	cursor = (char *) s;
	c = (int)(char) c;
	while (*cursor != '\0')
	{
		if (*cursor == c)
			return (cursor);
		cursor++;
	}
	if (c == '\0')
		return (cursor);
	else
		return (NULL);
}

char	*ft_strrchr(const char *s, int c)
{
	char	*cursor;

	cursor = (char *) s;
	c = (int)(char) c;
	while (*cursor != '\0')
		cursor++;
	while (1)
	{
		if (*cursor == c)
			return (cursor);
		if (cursor == s)
			return (NULL);
		cursor--;
	}
}

char	*ft_strmapi(char const *s, char (*f)(t_uint, char))
{
	char	*buf;
	t_uint	i;
	size_t	len;

	len = ft_strlen(s);
	buf = malloc(sizeof(char) * (len + 1));
	if (!buf)
		return (NULL);
	i = 0;
	while (i < len)
	{
		buf[i] = f(i, s[i]);
		i++;
	}
	buf[i] = '\0';
	return (buf);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	idx;

	idx = 0;
	while (!(s1[idx] == '\0' && s2[idx] == '\0') && idx < n)
	{
		if (s1[idx] != s2[idx])
			return ((int)((t_uchar)s1[idx] - (t_uchar)s2[idx]));
		idx++;
	}
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*cursor;
	size_t	l_needle;
	size_t	l_haystack;

	l_needle = ft_strlen(needle);
	l_haystack = ft_strlen(haystack);
	if (len < l_haystack)
		l_haystack = len;
	if (l_haystack < l_needle)
		return (NULL);
	l_haystack = l_haystack - l_needle + 1;
	cursor = (char *) haystack;
	if (l_needle == 0)
		return (cursor);
	while (l_haystack > 0)
	{
		if (ft_strncmp(cursor, needle, l_needle) == 0)
			return (cursor);
		cursor++;
		l_haystack--;
	}
	return (NULL);
}
