#include <stdio.h>

#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "material.h"
#include "geometry.h"
#include "number.h"
#include "hittable_internal.h"

static t_bool	ray_and_outward_norm_perpendicular(const t_ray *ray,
													t_vec3 *norm)
{
	if (fabs(vec3_dot_vec3(&ray->dir, norm)) < DOUBLE_E)
		return (TRUE);
	return (FALSE);
}

static void	set_u_axis_vec(t_vec3 *u_axis, t_vec3 *norm)
{
	const t_vec3	x_axis = {1, 0, 0};
	const t_vec3	y_axis = {0, 1, 0};

	if (fabs(norm->i[0]) > 0.9)
		vec3_cross_vec3(u_axis, &y_axis, norm);
	else
		vec3_cross_vec3(u_axis, &x_axis, norm);
	vec3_unitize(u_axis);
	//vec3_mult_num_inplace(u_axis, 0.2);
}

// 기본 박스 크기: 1 / freq
// 벡터 t 실수배 후 박스 크기: 기본 박스 크기 / t ---> 1 / (freq * t)
// The point O is origin in new u-v coordinates system.

// freq값을 텍스쳐에서 꺼내오는 건 불가능
// 식을 수정하는게 맞을듯
// 혜유킴님이 도와준다고 했음 님만 믿겠습니다.
static void	plane_set_uv(t_hittable_plane *plane, t_hit_record *rec)
{
	t_vec3	u_axis;
	t_vec3	v_axis;
	t_vec3	op;
	//double	tmp;
	double	u_on;
	double	v_on;

	set_u_axis_vec(&u_axis, &rec->normal);
	vec3_cross_vec3(&v_axis, &u_axis, &rec->normal);
	vec3_unitize(&v_axis);
	//vec3_mult_num_inplace(&v_axis, 0.2);
	vec3_sub_vec3(&op, &rec->p, &plane->point);
	// 실수배에서 1 / freq 곱
	vec3_mult_num_inplace(&op, 1 / freq);
	u_on = vec3_dot_vec3(&op, &u_axis);
	v_on = vec3_dot_vec3(&op, &v_axis);
	// 분모에 박스크기, 박스 크기가 곧 freq가 됨
	rec->uv.i[0] = fabs(floor(u_on)) / freq;
	rec->uv.i[1] = fabs(floor(v_on)) / freq; 
	/*
	if (u_on * v_on > 0)
	{
		rec->uv.i[0] = fabs(modf(u_on, &tmp));
		rec->uv.i[1] = fabs(modf(v_on, &tmp));
	}
	*/
	/*
	else
	{
		if (u_on > 0)
			rec->uv.i[0] = fabs(modf(u_on + 0.5, &tmp));
		else
			rec->uv.i[0] = fabs(modf(u_on - 0.5, &tmp));
		rec->uv.i[1] = fabs(modf(v_on, &tmp));
	}
	*/
	dprintf(2, "u: %f\n", rec->uv.i[0]);
	dprintf(2, "v: %f\n", rec->uv.i[1]);
	dprintf(2, "\n\n");
}

/*
static void	set_uv(t_uv *out,
				const t_hit_record *rec, const t_hittable_plane *this)
{
	double	distance;
	t_vec3	projected_p;
	t_vec3	x;
	t_vec3	z;

	distance = vec3_dot_vec3(&rec->p, &this->norm);
	vec3_mult_num(&projected_p, &this->norm, -distance);
	vec3_add_vec3_inplace(&projected_p, &rec->p);
	vec3_setval(&x, 1, 0, 0);
	vec3_setval(&z, 0, 0, 1);
	vec2_setval(
		out,
		fmod(vec3_dot_vec3(&x, &projected_p) / this->scale, 1.0),
		fmod(vec3_dot_vec3(&z, &projected_p) / this->scale, 1.0));
	if (out->i[0] < 0)
		out->i[0] += 1.0;
	if (out->i[1] < 0)
		out->i[1] += 1.0;
}
*/

/*
	This function needs to solve equation system of plane and straight line. 
	See the comment of the solver_equation_system_plane_and_line for details.
*/
t_bool	hit_plane(t_hittable *hittable,
					const t_ray *ray,
					t_minmax t,
					t_hit_record *rec)
{
	t_hittable_plane	*this;
	double				root;

	this = (t_hittable_plane *)hittable;
	if (ray_and_outward_norm_perpendicular(ray, &this->norm))
		return (FALSE);
	if (solver_equation_system_plane_and_line(t, this, ray, &root) == FALSE)
		return (FALSE);
	rec->t = root;
	ray_at(&rec->p, ray, rec->t);
	hit_record_set_normal_and_face(rec, ray, &this->norm);
	rec->material = this->material;
	plane_set_uv(this, rec);
	//set_uv(&rec->uv, rec, this);
	return (TRUE);
}

t_hittable	*hittable_plane_create(t_point point,
							t_vec3 norm,
							t_material *material,
							double scale)
{
	t_hittable_plane	*plane;

	plane = malloc(sizeof(t_hittable_plane));
	if (!plane)
		return (NULL);
	ft_memset(plane, 0, sizeof(t_hittable_plane));
	plane->destroy = hittable_destroy;
	plane->hit = hit_plane;
	plane->material = material;
	plane->point = point;
	plane->norm = norm;
	plane->scale = scale;

	return ((t_hittable *)plane);
}
