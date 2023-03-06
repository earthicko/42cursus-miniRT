/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse_format.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:14:38 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:49 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int	add_plain_text(t_list **convs, char *s, char *e)
{
	t_conv	*new_conv;
	t_list	*new_node;

	new_conv = create_conv();
	if (!new_conv)
		return (CODE_ERROR_MALLOC);
	new_conv->i_conv = PLAIN;
	new_conv->s = s;
	new_conv->e = e;
	new_node = ft_lstnew(new_conv);
	if (!new_node)
	{
		del_conv(new_conv);
		return (CODE_ERROR_MALLOC);
	}
	ft_lstadd_back(convs, new_node);
	return (CODE_OK);
}

static int	add_conversion(t_list **convs, t_conv *conv, char *s, char **fmt)
{
	t_list	*new_node;

	conv->s = s;
	conv->e = *fmt;
	new_node = ft_lstnew(conv);
	if (!new_node)
	{
		del_conv(conv);
		return (CODE_ERROR_MALLOC);
	}
	ft_lstadd_back(convs, new_node);
	return (CODE_OK);
}

static int	parse_conversion(t_list **convs, char **format)
{
	t_conv	*new_conv;
	char	*start;

	new_conv = create_conv();
	if (!new_conv)
		return (CODE_ERROR_MALLOC);
	start = *format;
	parse_printf_flags(new_conv, format);
	parse_printf_minwidth(new_conv, format);
	parse_printf_precision(new_conv, format);
	if (parse_printf_conv(new_conv, format) != CODE_OK)
	{
		del_conv(new_conv);
		return (CODE_ERROR_GENERIC);
	}
	return (add_conversion(convs, new_conv, start, format));
}

int	parse_format(t_list **convs, const char *format)
{
	char	*cursor;
	char	*temp;

	cursor = (char *)format;
	while (*cursor != '\0')
	{
		if (*cursor == '%')
		{
			if (parse_conversion(convs, &cursor) == CODE_ERROR_MALLOC)
				return (CODE_ERROR_MALLOC);
		}
		else
		{
			temp = cursor;
			while (*cursor != '%' && *cursor != '\0')
				cursor++;
			if (add_plain_text(convs, temp, cursor) < 0)
				return (CODE_ERROR_MALLOC);
		}
	}
	return (CODE_OK);
}
