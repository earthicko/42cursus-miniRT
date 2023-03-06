/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fwrite_ptr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:14:35 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:48 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_printf.h"
#include "libft.h"

static int	ft_ptrlen(void *ptr)
{
	t_uchar	*cursor;
	int		len;

	len = sizeof(ptr) * 2;
	cursor = (t_uchar *)(&ptr) + sizeof(ptr) - 1;
	while (len > 0)
	{
		if (*cursor / 16 != 0)
			break ;
		len--;
		if (*cursor % 16 != 0)
			break ;
		len--;
		cursor--;
	}
	return (len);
}

static char	*cstr_ptr_prefix(t_conv *conv, int len_ptr)
{
	int		res;
	char	*buf;
	char	*temp;

	buf = ft_strdup(PREFIX_LHEX);
	if (!buf)
		return (NULL);
	if (conv->f_precision && conv->precision > len_ptr)
	{
		temp = cstr_nchars(conv->precision - len_ptr, CHARSET_LHEX[0]);
		if (!temp)
		{
			free(buf);
			return (NULL);
		}
		res = ft_strappend(&buf, temp);
		free(temp);
		if (res < 0)
		{
			free(buf);
			return (NULL);
		}
	}
	return (buf);
}

static void	cstr_ptr_fill_str(void *ptr, int len_ptr, char *buf)
{
	t_uchar	*cursor;
	int		i;

	cursor = (t_uchar *)(&ptr) + sizeof(ptr) - 1;
	i = -(sizeof(ptr) * 2) + len_ptr;
	while (i < len_ptr)
	{
		if (i >= 0)
			buf[i] = CHARSET_LHEX[*cursor / 16];
		i++;
		if (i >= 0)
			buf[i] = CHARSET_LHEX[*cursor % 16];
		i++;
		cursor--;
	}
	buf[len_ptr] = '\0';
}

static char	*cstr_ptr_unsigned(t_conv *conv, void *ptr, int len_ptr)
{
	char			*buf;

	if (ptr == NULL)
	{
		if (conv->f_precision)
			return (ft_strdup(""));
		else
			return (ft_substr(CHARSET_LHEX, 0, 1));
	}
	buf = malloc(sizeof(char) * (len_ptr + 1));
	if (!buf)
		return (NULL);
	cstr_ptr_fill_str(ptr, len_ptr, buf);
	return (buf);
}

int	fwrite_ptr(int fd, t_conv *conv, void *ptr)
{
	int		res;
	char	*buf[4];
	int		len_ptr;

	len_ptr = ft_ptrlen(ptr);
	buf[1] = cstr_ptr_prefix(conv, len_ptr);
	buf[2] = cstr_ptr_unsigned(conv, ptr, len_ptr);
	buf[3] = cstr_padding(conv, ft_strlen(buf[1]) + ft_strlen(buf[2]));
	buf[0] = merge_num_buffers(conv, buf);
	if (!buf[0])
	{
		abort_fwrite(buf);
		return (CODE_ERROR_MALLOC);
	}
	res = write(fd, buf[0], ft_strlen(buf[0]));
	abort_fwrite(buf);
	if (res < 0)
		return (res);
	return (res);
}
