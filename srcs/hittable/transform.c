#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "geometry.h"
#include "hittable_internal.h"

t_bool	hittable_transform_hit(t_hittable *self,
			const t_ray *r, t_minmax t, t_hit_record *rec)
{
	t_hittable_transform	*this;
	t_ray					r_trans;

	this = (t_hittable_transform *)self;
	ray_multiply_m44(&r_trans, r, &this->w_to_o);
	if (!this->base->hit(this->base, &r_trans, t, rec))
		return (FALSE);
	vec3_multiply_m44_inplace(&rec->p, &this->o_to_w);
	vec3_multiply_m44_inplace(&rec->normal, &this->o_to_w);
	return (TRUE);
}

static t_point	get_corner(t_hittable_transform *this,
			t_point *(targets[2]), int i)
{
	t_point	corner;

	vec3_setval(&corner,
		targets[(i & 1) == 0]->i[0],
		targets[(i & 2) == 0]->i[1],
		targets[(i & 4) == 0]->i[2]);
	vec3_multiply_m44_inplace(&corner, &this->o_to_w);
	return (corner);
}

static void	hittable_transform_init_bbox(t_hittable_transform *this)
{
	int		i;
	t_point	corner;
	t_point	*(targets[2]);
	t_point	min;
	t_point	max;

	if (!hittable_has_bbox(this->base))
		return ;
	targets[0] = &this->base->bbox.min;
	targets[1] = &this->base->bbox.max;
	vec3_setval(&min, DOUBLE_INF, DOUBLE_INF, DOUBLE_INF);
	vec3_setval(&max, -DOUBLE_INF, -DOUBLE_INF, -DOUBLE_INF);
	i = 0;
	while (i < 8)
	{
		corner = get_corner(this, targets, i);
		vec3_min(&min, &min, &corner);
		vec3_max(&max, &max, &corner);
		i++;
	}
	bbox_init(&this->bbox, min, max);
}

static void	hittable_transform_init_o_to_w(t_mtx44 *o_to_w,
				t_point orig, t_vec3 rotate_angles)
{
	int	i;

	m44_init_identity(o_to_w);
	i = 0;
	while (i < 3)
	{
		m44_rotate_inplace(o_to_w, i, rotate_angles.i[i]);
		i++;
	}
	m44_translate_inplace(o_to_w, &orig);
}

t_hittable	*hittable_transform_create(t_hittable *base,
				t_point orig, t_vec3 rotate_angles)
{
	t_hittable_transform	*transform;

	transform = malloc(sizeof(t_hittable_transform));
	if (!transform)
		return (NULL);
	ft_bzero(transform, sizeof(t_hittable_transform));
	transform->destroy = hittable_destroy;
	transform->hit = hittable_transform_hit;
	transform->base = base;
	hittable_transform_init_o_to_w(&transform->o_to_w, orig, rotate_angles);
	m44_get_inverse(&transform->w_to_o, &transform->o_to_w);
	hittable_transform_init_bbox(transform);
	return ((t_hittable *)transform);
}
