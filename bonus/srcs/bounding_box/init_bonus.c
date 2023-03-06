/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include <libft.h>
#include "bounding_box_bonus.h"

t_bool	bbox_hit(t_bbox *this, const t_ray *r, const t_minmax *t)
{
	int		i;
	double	min;
	double	max;

	i = 0;
	while (i < 3)
	{
		min = fmax(
				fmin((this->min.i[i] - r->orig.i[i]) / r->dir.i[i],
					(this->max.i[i] - r->orig.i[i]) / r->dir.i[i]),
				t->min);
		max = fmin(
				fmax((this->min.i[i] - r->orig.i[i]) / r->dir.i[i],
					(this->max.i[i] - r->orig.i[i]) / r->dir.i[i]),
				t->max);
		if (max <= min)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	bbox_init(t_bbox *target, t_point min, t_point max)
{
	target->hit = bbox_hit;
	target->min = min;
	target->max = max;
}

void	bbox_init_surrounding(t_bbox *target, const t_bbox *a, const t_bbox *b)
{
	t_point	min;
	t_point	max;

	vec3_min(&min, &a->min, &b->min);
	vec3_max(&max, &a->max, &b->max);
	if (a->hit == 0 || b->hit == 0)
	{
		ft_bzero(target, sizeof(t_bbox));
		return ;
	}
	return (bbox_init(target, min, max));
}
