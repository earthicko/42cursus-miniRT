#ifndef HITTABLE_H
# define HITTABLE_H

# include "ray.h"
# include "hit_record_dummy.h"


typedef struct s_pair
{
	double	t_min;
	double	t_max;
}	t_pair;

typedef struct s_hittable	t_hittable;

typedef t_bool (*t_hit)(t_hittable *hittable, t_ray r, \
												t_pair t, t_hit_record *rec);	
typedef t_bool (*t_bounding_box)();

typedef struct s_hittable
{
	t_hit			hit;
	t_bounding_box	bounding_box;
}	t_hittable;

#endif