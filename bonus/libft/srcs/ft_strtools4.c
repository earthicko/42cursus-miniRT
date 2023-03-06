/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtools4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:14:31 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:50 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "libft.h"

int	ft_strappend(char **body, const char *tail)
{
	char	*temp;

	if (!tail)
		return (CODE_ERROR_GENERIC);
	temp = ft_strjoin(*body, tail);
	if (!temp)
		return (CODE_ERROR_MALLOC);
	free(*body);
	*body = temp;
	return (CODE_OK);
}

char	*ft_strmerge(int n_str, ...)
{
	char	*buf;
	char	*temp;
	va_list	p_args;
	int		i;

	buf = ft_strdup("");
	if (!buf)
		return (NULL);
	va_start(p_args, n_str);
	i = 0;
	while (i < n_str)
	{
		temp = va_arg(p_args, char *);
		if (ft_strappend(&buf, temp) < 0)
		{
			va_end(p_args);
			free(buf);
			return (NULL);
		}
		i++;
	}
	va_end(p_args);
	return (buf);
}

int	is_samestr(char *str1, char *str2)
{
	return (ft_strncmp(str1, str2, ft_strlen(str2) + 1) == 0);
}
