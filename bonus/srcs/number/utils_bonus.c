/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "number_bonus.h"

int	is_near_zero(double num)
{
	return (-DOUBLE_E < num && num < DOUBLE_E);
}

double	map_minmax(double x, const t_minmax *in, const t_minmax *out)
{
	return ((x - in->min) * (out->max - out->min)
		/ (in->max - in->min) + out->min);
}

int	clamp_int(int x, int min, int max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

void	swap_double(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
