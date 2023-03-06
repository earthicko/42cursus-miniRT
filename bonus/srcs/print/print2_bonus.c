/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2_bonus.c                                     :+:      :+:    :+:   */
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

void	print_aa_rect(const t_hittable *hittable)
{
	t_hittable_aa_rectangle	*aarect;

	aarect = (t_hittable_aa_rectangle *)hittable;
	printf("aa rect (axis %d, offset %.2f, ",
		aarect->axis, aarect->offset);
	printf("range %.2f ... %.2f, %.2f ... %.2f, norm ",
		aarect->range[0].min, aarect->range[0].max,
		aarect->range[1].min, aarect->range[1].max);
	print_vec3(&aarect->outward_norm);
	printf(")");
}

void	print_box(const t_hittable *box)
{
	t_hittable_transform	*tbox;
	t_hittable_aa_box		*aabox;
	int						i;

	tbox = (t_hittable_transform *)box;
	aabox = (t_hittable_aa_box *)tbox->base;
	printf("box object to world (transform): \n");
	print_mtx44(&tbox->otow_trans);
	printf("box object to world (rotation): \n");
	print_mtx44(&tbox->otow_rotate);
	i = 0;
	while (i < 6)
	{
		print_aa_rect(((t_hittable_list *)aabox->faces)->elements->data[i]);
		printf("\n");
		i++;
	}
	printf("aa box bounding box: ");
	print_bbox(&aabox->bbox);
	printf(" box bounding box: ");
	print_bbox(&tbox->bbox);
}
