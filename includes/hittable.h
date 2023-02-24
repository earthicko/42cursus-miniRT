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

void				hit_record_set_normal_and_face(
						t_hit_record *hit, t_ray *ray, t_vec3 *normal);

typedef struct s_minmax
{
	double	min;
	double	max;
}	t_minmax;

typedef struct s_hittable	t_hittable;

typedef t_bool				(*t_hittable_hit)(
		t_hittable *hittable, t_ray *r, t_minmax t, t_hit_record *rec);	
typedef t_bool				(*t_bounding_box)(void);

typedef struct s_hittable
{
	t_hittable_hit	hit;
	t_bounding_box	bounding_box;
	t_material		*material;
}	t_hittable;

typedef struct s_hittable_transform
{
	t_hittable_hit	hit;
	t_bounding_box	bounding_box;
	t_material		*material;
	t_hittable		*base;
	t_mtx44			transform;
}	t_hittable_transform;

typedef struct s_hittable_sphere
{
	t_hittable_hit	hit;
	t_bounding_box	bounding_box;
	t_material		*material;
	double			radius;
	t_point			center;
}	t_hittable_sphere;

typedef struct s_hittable_plane
{
	t_hittable_hit	hit;
	t_bounding_box	bounding_box;
	t_material		*material;
	t_point			point;
	t_vec3			norm;
}	t_hittable_plane;

typedef struct s_hittable_tube
{
	t_hittable_hit	hit;
	t_bounding_box	bounding_box;
	t_material		*material;
	t_point			center;
	t_vec3			axis;
	double			height;
	double			radius;
}	t_hittable_tube;

typedef struct s_hittable_disk
{
	t_hittable_hit			hit;
	t_bounding_box			bounding_box;
	t_material				*material;
	t_hittable_plane		plane;
	double					radius;
}	t_hittable_disk;

typedef struct s_hittable_cylinder
{
	t_hittable_hit	hit;
	t_bounding_box	bounding_box;
	t_material		*material;
	t_hittable_tube	*tube;
	t_hittable_disk	*disk[2];
}	t_hittable_cylinder;

typedef struct s_hittable_list
{
	t_hittable_hit	hit;
	t_bounding_box	bounding_box;
	t_material		*material;
	t_ptrarr		*elements;
}	t_hittable_list;

// TODO: 왜 함수가 여기있지..? 확인후 삭제할 것
t_hittable_sphere	*sphere_create(
						t_point center,
						double radius,
						t_material *material);

#endif
