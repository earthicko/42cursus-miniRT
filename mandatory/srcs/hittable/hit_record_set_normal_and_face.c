/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_record_set_normal_and_face.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"
#include "ray.h"

void	hit_record_set_normal_and_face(
			t_hit_record *rec, const t_ray *ray, const t_vec3 *normal)
{
	if (vec3_dot_vec3(&ray->dir, normal) < 0)
	{
		rec->is_front = TRUE;
		rec->normal = *normal;
	}
	else
	{
		rec->is_front = FALSE;
		vec3_mult_num(&rec->normal, normal, -1);
	}
}
