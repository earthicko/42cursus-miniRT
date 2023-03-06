/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fwrite_num.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:14:34 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:48 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"
#include "libft.h"

int	fwrite_int(int fd, t_conv *conv, int num, char *charset)
{
	int		res;
	char	*buf[4];

	buf[1] = cstr_prefix(conv, num, ft_strlen(charset));
	buf[2] = cstr_nbr(conv, num, charset);
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

int	fwrite_uint(int fd, t_conv *conv, t_uint num, char *charset)
{
	int		res;
	char	*buf[4];

	buf[1] = cstr_prefix(conv, num, ft_strlen(charset));
	buf[2] = cstr_nbr(conv, num, charset);
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
