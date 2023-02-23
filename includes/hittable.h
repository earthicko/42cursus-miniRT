#ifndef HITTABLE_H
# define HITTABLE_H

# include "geometry.h"
# include "ptrarr.h"
# include "ray.h"
# include "material.h"

typedef struct s_material	t_material;

typedef struct s_hit_record
{
	t_point		p;
	t_vec3		normal;
	t_material	*material;
	double		t;
	t_uv		uv;
	t_bool		is_front;
}	t_hit_record;

void	hit_record_set_normal_and_face(
			t_hit_record *hit, t_ray *ray, t_vec3 *normal);

typedef struct s_pair
{
	double	min;
	double	max;
}	t_pair;

typedef struct s_hittable	t_hittable;

typedef t_bool				(*t_hit)(
		t_hittable *hittable, t_ray *r, t_pair t, t_hit_record *rec);	
typedef t_bool				(*t_bounding_box)(void);

typedef struct s_hittables
{
	t_hit		hit;
	t_ptrarr	arr;
}	t_hittables;

typedef struct s_hittable
{
	t_hit			hit;
	t_bounding_box	bounding_box;
}	t_hittable;

#endif
