/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_dot_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "geometry_bonus.h"

double	vec3_dot_vec3(const t_vec3 *a, const t_vec3 *b)
{
	double	out;
	int		i;

	out = 0;
	i = 0;
	while (i < 3)
	{
		out += a->i[i] * b->i[i];
		i++;
	}
	return (out);
}
