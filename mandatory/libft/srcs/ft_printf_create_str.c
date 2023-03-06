/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_create_str.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:14:24 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:48 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"
#include "libft.h"

char	*cstr_nchars(int n, char c)
{
	char	*buf;
	int		i;

	buf = malloc(sizeof(char) * (n + 1));
	if (!buf)
		return (NULL);
	i = 0;
	while (i < n)
	{
		buf[i] = c;
		i++;
	}
	buf[i] = '\0';
	return (buf);
}

char	*cstr_nbr(t_conv *conv, t_ll nbr, char *charset)
{
	int		len_nbr;
	int		len_base;
	char	*buf;

	if (nbr == 0)
	{
		if (conv->f_precision)
			return (ft_strdup(""));
		else
			return (ft_substr(charset, 0, 1));
	}
	len_base = ft_strlen(charset);
	len_nbr = ft_numlen_base(nbr, len_base);
	buf = malloc(sizeof(char) * (len_nbr + 1));
	if (!buf)
		return (NULL);
	cstr_nbr_fill_str(buf, nbr, charset, len_base);
	buf[len_nbr] = '\0';
	return (buf);
}

char	*cstr_prefix(t_conv *conv, t_ll num, t_ll base)
{
	char	*buf;

	buf = cstr_sign(conv, num);
	if (!buf)
		return (NULL);
	if (append_hex_prefix(conv, num, base, &buf) < 0)
	{
		free(buf);
		return (NULL);
	}
	if (append_precision(conv, num, base, &buf) < 0)
	{
		free(buf);
		return (NULL);
	}
	return (buf);
}

char	*cstr_padding(t_conv *conv, int len_rest)
{
	int		len_pad;
	char	*padding;

	len_pad = 0;
	if (conv->f_minwidth && conv->minwidth > len_rest)
		len_pad = conv->minwidth - len_rest;
	if (conv->f_zeropad && !conv->f_precision && !conv->f_left)
		padding = cstr_nchars(len_pad, SYMBOL_ZEROPAD);
	else
		padding = cstr_nchars(len_pad, SYMBOL_BLANK);
	if (!padding)
		return (NULL);
	return (padding);
}
