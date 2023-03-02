#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "geometry.h"
#include "material.h"
#include "hittable_internal.h"

static double	get_root(t_hittable_aa_rectangle *this,
				const t_ray *ray, const t_minmax *t, const t_vec3 *outward_norm)
{
	double	root;

	if (fabs(vec3_dot_vec3(&ray->dir, outward_norm)) < DOUBLE_E)
		return (nan(0));
	root = (this->offset - ray->orig.i[this->axis]) / ray->dir.i[this->axis];
	if (root < t->min || root > t->max)
		return (nan(0));
	return (root);
}

static t_bool	is_outof_range(t_hittable_aa_rectangle *this, const t_point *p)
{
	if (p->i[this->other_axis[0]] < this->range[0].min)
		return (TRUE);
	if (p->i[this->other_axis[0]] > this->range[0].max)
		return (TRUE);
	if (p->i[this->other_axis[1]] < this->range[1].min)
		return (TRUE);
	if (p->i[this->other_axis[1]] > this->range[1].max)
		return (TRUE);
	return (FALSE);
}

t_bool	hit_aa_rectangle(t_hittable *hittable,
						const t_ray *ray,
						t_minmax t,
						t_hit_record *rec)
{
	t_hittable_aa_rectangle	*this;
	t_vec3					outward_norm;
	const t_minmax			uv_out = {0, 1};

	this = (t_hittable_aa_rectangle *)hittable;
	outward_norm.i[this->axis] = 1;
	outward_norm.i[this->other_axis[0]] = 0;
	outward_norm.i[this->other_axis[1]] = 0;
	rec->t = get_root(this, ray, &t, &outward_norm);
	if (rec->t != rec->t)
		return (FALSE);
	ray_at(&rec->p, ray, rec->t);
	if (is_outof_range(this, &rec->p))
		return (FALSE);
	rec->material = this->material;
	hit_record_set_normal_and_face(rec, ray, &outward_norm);
	vec2_setval(&rec->uv,
		map_minmax(rec->p.i[this->other_axis[0]], &this->range[0], &uv_out),
		map_minmax(rec->p.i[this->other_axis[1]], &this->range[1], &uv_out));
	return (TRUE);
}

t_hittable	*hittable_aa_rectangle_create(t_aa_rectangle_info info,
											t_material *material)
{
	const int				other_axises[3][2] = {{1, 2}, {2, 0}, {0, 1}};
	t_hittable_aa_rectangle	*aa_rect;

	if (info.axis < AXIS_X || info.axis > AXIS_Z)
		return (NULL);
	if (info.range[0].min > info.range[0].max
		|| info.range[1].min > info.range[1].max)
		return (NULL);
	aa_rect = malloc(sizeof(t_hittable_aa_rectangle));
	if (!aa_rect)
		return (NULL);
	ft_memset(aa_rect, 0, sizeof(t_hittable_aa_rectangle));
	aa_rect->hit = hit_aa_rectangle;
	aa_rect->material = material;
	aa_rect->axis = info.axis;
	aa_rect->offset = info.offset;
	aa_rect->other_axis[0] = other_axises[info.axis][0];
	aa_rect->other_axis[1] = other_axises[info.axis][1];
	aa_rect->range[0] = info.range[0];
	aa_rect->range[1] = info.range[1];
	return ((t_hittable *)aa_rect);
}
