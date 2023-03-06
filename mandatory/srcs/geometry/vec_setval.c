/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_setval.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

void	vec3_setval(t_vec3 *out, double a, double b, double c)
{
	out->i[0] = a;
	out->i[1] = b;
	out->i[2] = c;
}

void	vec2_setval(t_vec2 *out, double a, double b)
{
	out->i[0] = a;
	out->i[1] = b;
}
