/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_def.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:10:37 by donghyle          #+#    #+#             */
/*   Updated: 2022/07/08 12:10:39 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_DEF_H
# define FT_PRINTF_DEF_H

# define SYMBOL_NULL "(null)"
# define CHARSET_DEC "0123456789"
# define CHARSET_LHEX "0123456789abcdef"
# define CHARSET_UHEX "0123456789ABCDEF"
# define PREFIX_LHEX "0x"
# define PREFIX_UHEX "0X"
# define PREFIX_POS "+"
# define PREFIX_NEG "-"
# define PREFIX_BLANK " "
# define L_PREFIX_HEX 2
# define L_PREFIX_POS 1
# define L_PREFIX_NEG 1
# define L_PREFIX_BLANK 1

enum	e_symbol
{
	SYMBOL_ALTFORM = '#',
	SYMBOL_BLANK = ' ',
	SYMBOL_SIGN = '+',
	SYMBOL_LEFT = '-',
	SYMBOL_ZEROPAD = '0',
	SYMBOL_CHAR = 'c',
	SYMBOL_STR = 's',
	SYMBOL_PTR = 'p',
	SYMBOL_SDEC1 = 'd',
	SYMBOL_SDEC2 = 'i',
	SYMBOL_UDEC = 'u',
	SYMBOL_LHEX = 'x',
	SYMBOL_UHEX = 'X',
	SYMBOL_PCENT = '%'
};

enum e_conv
{
	PLAIN = 0,
	CHAR,
	STR,
	PTR,
	SDEC,
	UDEC,
	LHEX,
	UHEX,
	PCENT
};

typedef struct s_conv
{
	int		i_conv;
	char	*s;
	char	*e;
	int		minwidth;
	int		precision;
	int		f_left;
	int		f_zeropad;
	int		f_precision;
	int		f_minwidth;
	int		f_altform;
	int		f_blank;
	int		f_sign;
}	t_conv;

#endif
