/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memtools2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:10:11 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:47 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	ft_memmove_rtol(t_uchar *dst, t_uchar *src, size_t len)
{
	src += (len - 1);
	dst += (len - 1);
	while (len > 0)
	{
		(*dst) = (*src);
		dst--;
		src--;
		len--;
	}
}

static void	ft_memmove_ltor(t_uchar *dst, t_uchar *src, size_t len)
{
	while (len > 0)
	{
		(*dst) = (*src);
		dst++;
		src++;
		len--;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	t_uchar	*cursor_src;
	t_uchar	*cursor_dst;

	if (len == 0)
		return (dst);
	cursor_src = (t_uchar *) src;
	cursor_dst = (t_uchar *) dst;
	if (cursor_src == cursor_dst)
		return (dst);
	if (cursor_src < cursor_dst && cursor_dst < cursor_src + len)
		ft_memmove_rtol(cursor_dst, cursor_src, len);
	else
		ft_memmove_ltor(cursor_dst, cursor_src, len);
	return (dst);
}

static int	will_overflow_when_multiplied(size_t A, size_t B)
{
	size_t	result;

	if (A == 0 || B == 0)
		return (0);
	result = A * B;
	if (A == result / B)
		return (0);
	else
		return (1);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*output;
	size_t	n_bytes;

	if (will_overflow_when_multiplied(count, size))
		return (NULL);
	n_bytes = count * size;
	output = malloc(n_bytes);
	if (output)
		ft_bzero(output, n_bytes);
	return (output);
}
