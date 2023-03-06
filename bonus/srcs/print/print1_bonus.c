/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "hittable_bonus.h"
#include "ray_bonus.h"
#include "camera_bonus.h"
#include "print_bonus.h"

void	print_hit_record(const t_hit_record *rec)
{
	printf("hit record p");
	print_vec3(&rec->p);
	printf(" normal ");
	print_vec3(&rec->normal);
	printf(" %.2f ", rec->t);
	printf(" is front: %d material %s", rec->is_front, rec->material->name);
}

void	print_scatter_record(const t_scatter_record *rec)
{
	printf("scatter record color ");
	print_vec3(&rec->albedo);
	printf(" ray ");
	print_ray(&rec->scattered);
}

void	print_cylinder_info(const t_cylinder_info *info)
{
	printf("cylinder (center ");
	print_vec3(&info->center_of_cylinder);
	printf(", axis ");
	print_vec3(&info->axis);
	printf(", r %.2f h %.2f", info->radius, info->height);
	printf(")");
}

void	print_cone_info(const t_cone_info *info)
{
	printf("cone (center ");
	print_vec3(&info->center_of_disk);
	printf(", axis ");
	print_vec3(&info->axis);
	printf(", r %.2f h %.2f", info->radius, info->height);
	printf(")");
}

void	print_bbox(const t_bbox *bbox)
{
	printf("bbox (");
	if (bbox->hit == 0)
	{
		printf("empty");
	}
	else
	{
		print_vec3(&bbox->min);
		printf(" -> ");
		print_vec3(&bbox->max);
	}
	printf(")");
}
