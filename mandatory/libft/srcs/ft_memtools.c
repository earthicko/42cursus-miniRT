/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memtools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:10:13 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:47 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft_def.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	t_uchar	*cursor_1;
	t_uchar	*cursor_2;

	cursor_1 = (t_uchar *) s1;
	cursor_2 = (t_uchar *) s2;
	while (n > 0)
	{
		if (*cursor_1 != *cursor_2)
			return ((int)(*cursor_1) - (int)(*cursor_2));
		cursor_1++;
		cursor_2++;
		n--;
	}
	return (0);
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	t_uchar	*cursor;
	t_uchar	target;

	cursor = (t_uchar *) s;
	target = c;
	while (n > 0)
	{
		if (*cursor == target)
			return ((void *) cursor);
		cursor++;
		n--;
	}
	return (NULL);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	t_uchar	*cursor_src;
	t_uchar	*cursor_dst;

	if (dst == NULL && src == NULL)
		return (dst);
	cursor_src = (t_uchar *) src;
	cursor_dst = (t_uchar *) dst;
	while (n > 0)
	{
		n--;
		*cursor_dst = *cursor_src;
		cursor_src++;
		cursor_dst++;
	}
	return (dst);
}

void	*ft_memset(void *b, int c, size_t len)
{
	t_uchar	*cursor;
	t_uchar	content;

	content = (t_uchar) c;
	cursor = (t_uchar *) b;
	while (len > 0)
	{
		*cursor = content;
		cursor++;
		len--;
	}
	return (b);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
