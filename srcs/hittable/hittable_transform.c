#include <stdlib.h>
#include <math.h>
#include "geometry.h"
#include "hittable.h"

t_bool	hittable_transform_hit(t_hittable *self,
			t_ray *r, t_minmax t, t_hit_record *rec)
{
	t_hittable_transform	*this;
	t_ray					r_trans;

	this = (t_hittable_transform *)self;
	ray_multiply_m44(&r_trans, r, &this->w_to_h);
	if (!this->base->hit(this->base, &r_trans, t, rec))
		return (FALSE);
	vec3_multiply_m44_inplace(&rec->p, &this->h_to_w);
	vec3_multiply_m44_inplace(&rec->normal, &this->h_to_w);
	hit_record_set_normal_and_face(rec, &r_trans, &rec->normal);
	return (TRUE);
}

static void	hittable_transform_init_w_to_h(t_mtx44 *w_to_h,
				t_point orig, double ele, double azi)
{
	m44_init_identity(w_to_h);
	m44_translate_inplace(w_to_h, &orig);
	m44_rotate_inplace(w_to_h, AXIS_Z, -azi);
	m44_rotate_inplace(w_to_h, AXIS_X, -(M_PI_2 - ele));
}

static void	hittable_transform_init_h_to_w(t_mtx44 *h_to_w,
				t_point orig, double ele, double azi)
{
	orig.i[0] = -orig.i[0];
	orig.i[1] = -orig.i[1];
	orig.i[2] = -orig.i[2];
	m44_init_identity(h_to_w);
	m44_rotate_inplace(h_to_w, AXIS_X, M_PI_2 - ele);
	m44_rotate_inplace(h_to_w, AXIS_Z, azi);
	m44_translate_inplace(h_to_w, &orig);
}

t_hittable	*hittable_transform_create(t_hittable *base,
				t_point orig, double ele, double azi)
{
	t_hittable_transform	*transform;

	transform = malloc(sizeof(t_hittable_transform));
	if (!transform)
		return (NULL);
	transform->hit = hittable_transform_hit;
	transform->base = base;
	hittable_transform_init_w_to_h(&transform->w_to_h, orig, ele, azi);
	hittable_transform_init_h_to_w(&transform->h_to_w, orig, ele, azi);
	return ((t_hittable *)transform);
}
