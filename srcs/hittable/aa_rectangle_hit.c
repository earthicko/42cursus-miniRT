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
	const t_minmax			uv_out = {0, 1};

	this = (t_hittable_aa_rectangle *)hittable;
	if (!this->bbox.hit(&this->bbox, ray, &t))
		return (FALSE);
	rec->t = get_root(this, ray, &t, &this->outward_norm);
	if (rec->t != rec->t)
		return (FALSE);
	ray_at(&rec->p, ray, rec->t);
	if (is_outof_range(this, &rec->p))
		return (FALSE);
	rec->material = this->material;
	hit_record_set_normal_and_face(rec, ray, &this->outward_norm);
	vec2_setval(&rec->uv,
		map_minmax(rec->p.i[this->other_axis[0]], &this->range[0], &uv_out),
		map_minmax(rec->p.i[this->other_axis[1]], &this->range[1], &uv_out));
	if (this->outward_norm.i[this->axis] < 0)
		rec->uv.i[0] = 1 - rec->uv.i[0];
	return (TRUE);
}
