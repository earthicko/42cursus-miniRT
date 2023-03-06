/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fwrite_chr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:14:32 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:48 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_printf.h"
#include "libft.h"

int	fwrite_plain(int fd, t_conv *conv)
{
	return (write(fd, conv->s, conv->e - conv->s));
}

static int	fwrite_char_with_padding(int fd, t_conv *conv, int c, char *pad)
{
	t_uchar	buf;
	int		res;

	buf = c;
	if (!conv->f_left)
	{
		res = write(fd, pad, ft_strlen(pad));
		if (res < 0)
			return (res);
	}
	res = write(fd, &buf, 1);
	if (res < 0)
		return (res);
	if (conv->f_left)
	{
		res = write(fd, pad, ft_strlen(pad));
		if (res < 0)
			return (res);
	}
	return (CODE_OK);
}

int	fwrite_char(int fd, t_conv *conv, int c)
{
	int		n_put;
	int		res;
	char	*padding;

	n_put = 1;
	if (conv->f_minwidth && conv->minwidth > 1)
	{
		if (conv->f_zeropad && !conv->f_left)
			padding = cstr_nchars(conv->minwidth - 1, CHARSET_DEC[0]);
		else
			padding = cstr_nchars(conv->minwidth - 1, PREFIX_BLANK[0]);
		n_put += conv->minwidth - 1;
	}
	else
		padding = ft_strdup("");
	if (!padding)
		return (CODE_ERROR_MALLOC);
	res = fwrite_char_with_padding(fd, conv, c, padding);
	free(padding);
	if (res < 0)
		return (res);
	return (n_put);
}

int	fwrite_str(int fd, t_conv *conv, char *str)
{
	int		n_put;
	int		res;
	char	*buf;
	int		len_max;

	if (!str)
		str = SYMBOL_NULL;
	len_max = ft_strlen(str);
	if (conv->f_precision && conv->precision < len_max)
		len_max = conv->precision;
	buf = ft_substr(str, 0, len_max);
	if (!buf)
		return (CODE_ERROR_MALLOC);
	if (add_padding(conv, &buf) < 0)
	{
		free(buf);
		return (CODE_ERROR_MALLOC);
	}
	n_put = ft_strlen(buf);
	res = write(fd, buf, n_put);
	free(buf);
	if (res < 0)
		return (res);
	return (n_put);
}
