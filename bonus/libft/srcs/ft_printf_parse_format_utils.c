/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse_format_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:14:40 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:49 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int	is_printf_flag(char c)
{
	if (c == '#' || c == ' ' || c == '+' || c == '-' || c == '0')
		return (TRUE);
	return (FALSE);
}

void	parse_printf_flags(t_conv *conv, char **format)
{
	(*format)++;
	while (is_printf_flag(**format))
	{
		if (**format == SYMBOL_ALTFORM)
			conv->f_altform = TRUE;
		else if (**format == SYMBOL_BLANK)
			conv->f_blank = TRUE;
		else if (**format == SYMBOL_SIGN)
			conv->f_sign = TRUE;
		else if (**format == SYMBOL_LEFT)
			conv->f_left = TRUE;
		else if (**format == SYMBOL_ZEROPAD)
			conv->f_zeropad = TRUE;
		(*format)++;
	}
}

void	parse_printf_minwidth(t_conv *conv, char **format)
{
	char	*temp;

	temp = *format;
	while (ft_isdigit(**format))
		(*format)++;
	if (temp != *format)
	{
		conv->f_minwidth = TRUE;
		conv->minwidth = ft_atoi(temp);
	}
}

void	parse_printf_precision(t_conv *conv, char **format)
{
	char	*temp;

	if (**format == '.')
	{
		conv->f_precision = TRUE;
		(*format)++;
		temp = *format;
		while (ft_isdigit(**format))
			(*format)++;
		conv->precision = 0;
		if (temp != *format)
			conv->precision = ft_atoi(temp);
	}
}

int	parse_printf_conv(t_conv *conv, char **fmt)
{
	if (**fmt == SYMBOL_CHAR)
		conv->i_conv = CHAR;
	else if (**fmt == SYMBOL_STR)
		conv->i_conv = STR;
	else if (**fmt == SYMBOL_PTR)
		conv->i_conv = PTR;
	else if (**fmt == SYMBOL_SDEC1 || **fmt == SYMBOL_SDEC2)
		conv->i_conv = SDEC;
	else if (**fmt == SYMBOL_UDEC)
		conv->i_conv = UDEC;
	else if (**fmt == SYMBOL_LHEX)
		conv->i_conv = LHEX;
	else if (**fmt == SYMBOL_UHEX)
		conv->i_conv = UHEX;
	else if (**fmt == SYMBOL_PCENT)
		conv->i_conv = PCENT;
	else
	{
		conv->i_conv = CODE_ERROR_GENERIC;
		return (CODE_ERROR_GENERIC);
	}
	(*fmt)++;
	return (CODE_OK);
}
