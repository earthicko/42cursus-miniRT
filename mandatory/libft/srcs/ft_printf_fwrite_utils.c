/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fwrite_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:14:37 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:49 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"
#include "libft.h"

char	*merge_num_buffers(t_conv *conv, char **buf)
{
	char	*merged;

	if (buf[3][0] == SYMBOL_ZEROPAD)
		merged = ft_strmerge(3, buf[1], buf[3], buf[2]);
	else
	{
		if (conv->f_left)
			merged = ft_strmerge(3, buf[1], buf[2], buf[3]);
		else
			merged = ft_strmerge(3, buf[3], buf[1], buf[2]);
	}
	return (merged);
}

void	abort_fwrite(char **bufs)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (bufs[i])
			free(bufs[i]);
		i++;
	}
}

int	add_padding(t_conv *conv, char **buf)
{
	int		res;
	char	*padding;
	char	*temp;

	padding = cstr_padding(conv, ft_strlen(*buf));
	if (!padding)
		return (CODE_ERROR_MALLOC);
	if (!conv->f_left)
	{
		temp = *buf;
		*buf = padding;
		padding = temp;
	}
	res = ft_strappend(buf, padding);
	free(padding);
	if (res < 0)
		return (CODE_ERROR_MALLOC);
	return (CODE_OK);
}
