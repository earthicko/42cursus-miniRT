/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtools3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:10:21 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:50 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	l_s1;
	char	*dup;

	l_s1 = ft_strlen(s1);
	dup = malloc(sizeof(char) * (l_s1 + 1));
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s1, l_s1 + 1);
	return (dup);
}

void	ft_striteri(char *s, void (*f)(t_uint, char*))
{
	size_t	len;
	t_uint	i;

	len = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		f(i, s + i);
		i++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_1;
	size_t	len_2;
	char	*joined;

	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	joined = malloc(sizeof(char) * (len_1 + len_2 + 1));
	if (!joined)
		return (NULL);
	ft_memcpy(joined, s1, len_1);
	ft_memcpy(joined + len_1, s2, len_2);
	joined[len_1 + len_2] = '\0';
	return (joined);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_src;
	size_t	len_dst;
	size_t	i_src;
	size_t	i_dst;

	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	i_src = 0;
	i_dst = len_dst;
	if (dstsize > len_dst)
	{
		while (i_dst < dstsize - 1 && src[i_src] != '\0')
		{
			dst[i_dst] = src[i_src];
			i_src++;
			i_dst++;
		}
		dst[i_dst] = '\0';
	}
	if (dstsize < len_dst)
		return (len_src + dstsize);
	else
		return (len_src + len_dst);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	idx;

	src_len = ft_strlen(src);
	if (dstsize > 0)
	{
		idx = 0;
		while (src[idx] != '\0' && idx < dstsize - 1)
		{
			dst[idx] = src[idx];
			idx++;
		}
		dst[idx] = '\0';
	}
	return (src_len);
}
