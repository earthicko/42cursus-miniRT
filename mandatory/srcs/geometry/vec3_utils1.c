/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "geometry.h"
#include "number.h"

double	vec3_get_len(const t_vec3 *in)
{
	return (sqrt(
			in->i[0] * in->i[0]
			+ in->i[1] * in->i[1]
			+ in->i[2] * in->i[2]));
}

double	vec3_get_len_sq(const t_vec3 *in)
{
	return (in->i[0] * in->i[0]
		+ in->i[1] * in->i[1]
		+ in->i[2] * in->i[2]);
}

t_bool	vec3_is_near_zero(const t_vec3 *in)
{
	return (
		- DOUBLE_E < in->i[0] && in->i[0] < DOUBLE_E
		&& - DOUBLE_E < in->i[1] && in->i[1] < DOUBLE_E
		&& - DOUBLE_E < in->i[2] && in->i[2] < DOUBLE_E);
}

void	vec3_get_unit(t_vec3 *out, const t_vec3 *in)
{
	int		i;
	double	len;

	len = vec3_get_len(in);
	i = 0;
	while (i < 3)
	{
		out->i[i] = in->i[i] / len;
		i++;
	}
}

void	vec3_unitize(t_vec3 *target)
{
	t_vec3	temp;

	vec3_get_unit(&temp, target);
	ft_memcpy(target, &temp, sizeof(t_vec3));
}
