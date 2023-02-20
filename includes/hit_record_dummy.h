#ifndef HIT_RECORD_DUMMY_H
# define HIT_RECORD_DUMMY_H

# include "geometry.h"
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

void	hit_record_set_normal_and_face(t_ray *ray, t_vec3 *normal);

#endif
