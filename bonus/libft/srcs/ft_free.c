/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 13:48:26 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:47 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>

void	ft_free(int n_ptr, ...)
{
	va_list	p_args;
	void	*ptr;
	int		i;

	va_start(p_args, n_ptr);
	i = 0;
	while (i < n_ptr)
	{
		ptr = va_arg(p_args, void *);
		free(ptr);
		i++;
	}
	va_end(p_args);
}
