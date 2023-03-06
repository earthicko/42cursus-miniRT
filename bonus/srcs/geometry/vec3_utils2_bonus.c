/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "geometry_bonus.h"
#include "number_bonus.h"

void	vec3_rand(t_vec3 *out, double min, double max)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		out->i[i] = rand_double_range(min, max);
		i++;
	}
}

void	vec3_get_random_in_unit_sphere(t_vec3 *out)
{
	while (TRUE)
	{
		vec3_rand(out, -1, 1);
		if (vec3_get_len_sq(out) < 1.0)
			return ;
	}
}

void	vec3_get_random_unit(t_vec3 *out)
{
	vec3_get_random_in_unit_sphere(out);
	vec3_unitize(out);
}

void	vec3_min(t_vec3 *out, const t_vec3 *a, const t_vec3 *b)
{
	vec3_setval(out,
		fmin(a->i[0], b->i[0]),
		fmin(a->i[1], b->i[1]),
		fmin(a->i[2], b->i[2]));
}

void	vec3_max(t_vec3 *out, const t_vec3 *a, const t_vec3 *b)
{
	vec3_setval(out,
		fmax(a->i[0], b->i[0]),
		fmax(a->i[1], b->i[1]),
		fmax(a->i[2], b->i[2]));
}
