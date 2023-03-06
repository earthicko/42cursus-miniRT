#ifndef BOUNDING_BOX_H
# define BOUNDING_BOX_H

# include "number.h"
# include "geometry.h"
# include "ray.h"

typedef struct s_bbox	t_bbox;

typedef t_bool			(*t_bbox_hit)(t_bbox *self,
										const t_ray *r,
										const t_minmax *t);

typedef struct s_bbox
{
	t_bbox_hit	hit;
	t_point		min;
	t_point		max;
}	t_bbox;

void	bbox_init(t_bbox *target, t_point min, t_point max);
void	bbox_init_surrounding(t_bbox *target, const t_bbox *a, const t_bbox *b);

#endif
