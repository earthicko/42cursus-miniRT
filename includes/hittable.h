#ifndef HITTABLE_H
# define HITTABLE_H

# include "geometry.h"
# include "number.h"
# include "ptrarr.h"
# include "ray.h"
# include "material.h"
# include "bounding_box.h"

typedef struct s_material	t_material;

/******* hit_record *******/

typedef struct s_hit_record
{
	t_point		p;
	t_vec3		normal;
	t_material	*material;
	double		t;
	t_uv		uv;
	t_bool		is_front;
}	t_hit_record;

void				hit_record_set_normal_and_face(t_hit_record *rec, \
													const t_ray *ray, \
													const t_vec3 *normal);


/******* hittable abstract struct *******/

typedef struct s_hittable	t_hittable;

typedef t_bool				(*t_hittable_hit)(t_hittable *hittable,
												const t_ray *r,
												t_minmax t,
												t_hit_record *rec);

typedef struct s_hittable
{
	t_hittable_hit	hit;
	t_bbox			bbox;
}	t_hittable;

typedef struct s_hittable_transform
{
	t_hittable_hit	hit;
	t_bbox			bbox;
	t_hittable		*base;
	t_mtx44			w_to_h;
	t_mtx44			h_to_w;
}	t_hittable_transform;


/******* hittable real objects struct *******/

typedef struct s_hittable_sphere
{
	t_hittable_hit	hit;
	t_bbox			bbox;
	t_material		*material;
	double			radius;
	t_point			center;
}	t_hittable_sphere;

typedef struct s_hittable_plane
{
	t_hittable_hit	hit;
	t_bbox			bbox;
	t_material		*material;
	t_point			point;
	t_vec3			norm;
}	t_hittable_plane;

typedef struct s_hittable_tube
{
	t_hittable_hit	hit;
	t_bbox			bbox;
	t_material		*material;
	t_point			center_of_cylinder;
	t_point			center_of_disk;
	t_vec3			axis;
	double			height;
	double			radius;
}	t_hittable_tube;

typedef struct s_hittable_disk
{
	t_hittable_hit			hit;
	t_bbox					bbox;
	t_material				*material;
	t_hittable_plane		plane;
	double					radius;
}	t_hittable_disk;

typedef struct s_hittable_cylinder
{
	t_hittable_hit	hit;
	t_bbox			bbox;
	t_material		*material;
	t_hittable_tube	tube;
	t_hittable_disk	disk[2];
}	t_hittable_cylinder;

typedef struct s_cylinder_info
{
	t_point	center_of_cylinder;
	t_vec3	axis;
	double	height;
	double	radius;
}	t_cylinder_info;

typedef struct s_hittable_conical_hat
{
	t_hittable_hit	hit;
	t_bbox			bbox;
	t_material		*material;
	t_point			center_of_disk;
	t_vec3			axis;
	t_point			apex;
	double			height;
	double			radius;
}	t_hittable_conical_hat;

typedef struct s_hittable_cone
{
	t_hittable_hit			hit;
	t_bbox					bbox;
	t_material				*material;
	t_hittable_disk			disk;
	t_hittable_conical_hat	conical_hat;
}	t_hittable_cone;

typedef struct s_cone_info
{
	t_point	center_of_disk;
	t_vec3	axis;
	double	height;
	double	radius;
}	t_cone_info;

enum	e_disk_of_cylinder
{
	TOP = 0,
	BOTTOM
};

typedef struct s_hittable_list
{
	t_hittable_hit	hit;
	t_bbox			bbox;
	t_ptrarr		*elements;
}	t_hittable_list;


/******* hittable objects constructor, destructor *******/

t_hittable			*hittable_sphere_create(t_point center, \
											double radius, \
											t_material *material);
t_hittable			*hittable_plane_create(t_point point, \
											t_vec3 norm, \
											t_material *material);
t_hittable			*hittable_cylinder_create(t_cylinder_info *cylinder_info, \
												t_material *material);
t_hittable			*hittable_list_create(void);
t_hittable			*hittable_transform_create(t_hittable *base, \
												t_point orig, \
												double ele, \
												double azi);

void				hittable_list_destroy(t_hittable_list *list);

t_bool				hittable_has_bbox(t_hittable *self);
int					hittable_list_append(t_hittable *self, t_hittable *item);

#endif
