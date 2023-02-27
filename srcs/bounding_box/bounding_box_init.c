#include <stdlib.h>
#include <math.h>
#include <libft.h>
#include "bounding_box.h"

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
	const t_point	min = {
		fmin(a->min.i[0], b->min.i[0]),
		fmin(a->min.i[1], b->min.i[1]),
		fmin(a->min.i[2], b->min.i[2])};
	const t_point	max = {
		fmax(a->max.i[0], b->max.i[0]),
		fmax(a->max.i[1], b->max.i[1]),
		fmax(a->max.i[2], b->max.i[2])};

	if (a->hit == 0 || b->hit == 0)
	{
		ft_bzero(target, sizeof(t_bbox));
		return ;
	}
	return (bbox_init(target, min, max));
}
