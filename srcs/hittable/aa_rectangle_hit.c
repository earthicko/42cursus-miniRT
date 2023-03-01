#include <math.h>
#include "geometry.h"
#include "hittable_internal.h"

// TODO: x0, x1 대소 반드시 모든 함수에 대해 체크할 것
// TODO: implement u/v calculation
t_bool	hit_xy_rectangle(t_hittable *hittable,
						const t_ray *ray,
						t_minmax t,
						t_hit_record *rec)
{
	t_hittable_xy_rectangle	*this;
	const t_vec3			outward_norm = {0, 0, 1};
	double					root;
	t_point					p;

	this = (t_hittable_xy_rectangle *)hittable;
	if (fabs(vec3_dot_vec3(&ray->dir, &outward_norm)) < DOUBLE_E)
		return (FALSE);
	root = (this->k - ray->orig.i[Z]) / ray->dir.i[Z];
	if (root < t.min || root > t.max)
		return (FALSE);
	rec->t = root;
	ray_at(&p, ray, rec->t);
	if (p.i[X] < this->x0 || p.i[X] > this->x1
		|| p.i[Y] < this->y0 || p.i[Y] > this->y0)
		return (FALSE);
	hit_record_set_normal_and_face(rec, ray, &outward_norm);
	rec->material = this->material;
	vec2_setval(&rec->uv, 0, 0);
	return (TRUE);
}

// TODO: x0, x1 대소 반드시 모든 함수에 대해 체크할 것
// TODO: implement u/v calculation
t_bool	hit_yz_rectangle(t_hittable *hittable,
						const t_ray *ray,
						t_minmax t,
						t_hit_record *rec)
{
	t_hittable_yz_rectangle	*this;
	const t_vec3			outward_norm = {1, 0, 0};
	double					root;
	t_point					p;

	this = (t_hittable_yz_rectangle *)hittable;
	if (fabs(vec3_dot_vec3(&ray->dir, &outward_norm)) < DOUBLE_E)
		return (FALSE);
	root = (this->k - ray->orig.i[X]) / ray->dir.i[X];
	if (root < t.min || root > t.max)
		return (FALSE);
	rec->t = root;
	ray_at(&p, ray, rec->t);
	if (p.i[Y] < this->y0 || p.i[Y] > this->y1
		|| p.i[Z] < this->z0 || p.i[Z] > this->z1)
		return (FALSE);
	hit_record_set_normal_and_face(rec, ray, &outward_norm);
	rec->material = this->material;
	vec2_setval(&rec->uv, 0, 0);
	return (TRUE);
}

// TODO: x0, x1 대소 반드시 모든 함수에 대해 체크할 것
// TODO: implement u/v calculation
t_bool	hit_zx_rectangle(t_hittable *hittable,
						const t_ray *ray,
						t_minmax t,
						t_hit_record *rec)
{
	t_hittable_zx_rectangle	*this;
	const t_vec3			outward_norm = {0, 1, 0};
	double					root;
	t_point					p;

	this = (t_hittable_zx_rectangle *)hittable;
	if (fabs(vec3_dot_vec3(&ray->dir, &outward_norm)) < DOUBLE_E)
		return (FALSE);
	root = (this->k - ray->orig.i[Y]) / ray->dir.i[Y];
	if (root < t.min || root > t.max)
		return (FALSE);
	rec->t = root;
	ray_at(&p, ray, rec->t);
	if (p.i[Z] < this->z0 || p.i[Z] > this->z1
		|| p.i[X] < this->x0 || p.i[X] > this->x1)
		return (FALSE);
	hit_record_set_normal_and_face(rec, ray, &outward_norm);
	rec->material = this->material;
	vec2_setval(&rec->uv, 0, 0);
	return (TRUE);
}
