/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 13:48:26 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:47 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	handle_sign(const char **cursor, int *sign);
int		handle_number(const char *str, int *digits_after_dot, double *val);
void	handle_power(int digits_after_dot, double *val);

double	ft_atof(const char *str)
{
	static const long long	nan = 0x7ff8000000000000L;
	double					value;
	int						sign;
	int						digits_after_decimal;

	value = 0.0;
	handle_sign(&str, &sign);
	digits_after_decimal = 0;
	value = 0.0;
	if (handle_number(str, &digits_after_decimal, &value))
		return (*((double *)(&nan)));
	handle_power(digits_after_decimal, &value);
	value = value * sign;
	return (value);
}
