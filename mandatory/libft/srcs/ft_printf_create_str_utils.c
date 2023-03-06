/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_create_str_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:14:25 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:48 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"
#include "libft.h"

int	ft_numlen_base(t_ll num, t_ll base)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		num /= base;
		len++;
	}
	return (len);
}

int	cstr_nbr_fill_str(char *buf, t_ll nbr, char *base, int l_base)
{
	int	digit;
	int	i_digit;

	if (nbr == 0)
		return (0);
	digit = nbr % l_base;
	if (digit < 0)
		digit = -digit;
	i_digit = cstr_nbr_fill_str(buf, nbr / l_base, base, l_base);
	buf[i_digit] = base[digit];
	return (i_digit + 1);
}

char	*cstr_sign(t_conv *conv, t_ll num)
{
	if (num >= 0)
	{
		if (conv->i_conv != SDEC)
			return (ft_strdup(""));
		if (conv->f_sign)
			return (ft_strdup(PREFIX_POS));
		else if (conv->f_blank)
			return (ft_strdup(PREFIX_BLANK));
		return (ft_strdup(""));
	}
	else
		return (ft_strdup(PREFIX_NEG));
}

int	append_hex_prefix(t_conv *conv, t_ll num, t_ll base, char **buf)
{
	if (base == 16 && conv->f_altform && num != 0)
	{
		if (conv->i_conv == LHEX && ft_strappend(buf, PREFIX_LHEX) < 0)
			return (CODE_ERROR_MALLOC);
		if (conv->i_conv == UHEX && ft_strappend(buf, PREFIX_UHEX) < 0)
			return (CODE_ERROR_MALLOC);
	}
	return (CODE_OK);
}

int	append_precision(t_conv *conv, t_ll num, t_ll base, char **buf)
{
	int		len_num;
	int		res;
	char	*temp;

	len_num = ft_numlen_base(num, base);
	if (conv->f_precision && conv->precision > len_num)
	{
		temp = cstr_nchars(conv->precision - len_num, CHARSET_LHEX[0]);
		if (!temp)
			return (CODE_ERROR_MALLOC);
		res = ft_strappend(buf, temp);
		free(temp);
		if (res < 0)
			return (CODE_ERROR_MALLOC);
	}
	return (CODE_OK);
}
