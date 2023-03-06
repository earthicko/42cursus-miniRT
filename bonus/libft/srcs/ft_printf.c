/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:14:29 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:48 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"
#include "libft.h"

static int	fwrite_conv(int fd, t_conv *cv, va_list p_args)
{
	if (cv->i_conv == PLAIN)
		return (fwrite_plain(fd, cv));
	else if (cv->i_conv == CHAR)
		return (fwrite_char(fd, cv, va_arg(p_args, int)));
	else if (cv->i_conv == STR)
		return (fwrite_str(fd, cv, va_arg(p_args, char *)));
	else if (cv->i_conv == PTR)
		return (fwrite_ptr(fd, cv, va_arg(p_args, void *)));
	else if (cv->i_conv == SDEC)
		return (fwrite_int(fd, cv, va_arg(p_args, int), CHARSET_DEC));
	else if (cv->i_conv == UDEC)
		return (fwrite_uint(fd, cv, va_arg(p_args, int), CHARSET_DEC));
	else if (cv->i_conv == LHEX)
		return (fwrite_uint(fd, cv, va_arg(p_args, int), CHARSET_LHEX));
	else if (cv->i_conv == UHEX)
		return (fwrite_uint(fd, cv, va_arg(p_args, int), CHARSET_UHEX));
	else if (cv->i_conv == PCENT)
		return (fwrite_char(fd, cv, SYMBOL_PCENT));
	else
		return (CODE_ERROR_GENERIC);
}

static int	fwrite_list(int fd, t_list *convs, va_list p_args)
{
	t_conv	*conv;
	int		n_put;
	int		res;

	n_put = 0;
	while (convs != NULL)
	{
		conv = convs->content;
		res = fwrite_conv(fd, conv, p_args);
		if (res < 0)
			return (res);
		n_put += res;
		convs = convs->next;
	}
	return (n_put);
}

int	ft_printf(const char *format, ...)
{
	va_list	p_args;
	t_list	*convs;
	int		res;

	convs = NULL;
	res = parse_format(&convs, format);
	if (res < 0)
	{
		ft_lstclear(&convs, del_conv);
		return (res);
	}
	va_start(p_args, format);
	res = fwrite_list(STDOUT_FILENO, convs, p_args);
	va_end(p_args);
	ft_lstclear(&convs, del_conv);
	return (res);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	p_args;
	t_list	*convs;
	int		res;

	convs = NULL;
	res = parse_format(&convs, format);
	if (res < 0)
	{
		ft_lstclear(&convs, del_conv);
		return (res);
	}
	va_start(p_args, format);
	res = fwrite_list(fd, convs, p_args);
	va_end(p_args);
	ft_lstclear(&convs, del_conv);
	return (res);
}
