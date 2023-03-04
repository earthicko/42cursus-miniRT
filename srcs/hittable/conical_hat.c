#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "geometry.h"
#include "number.h"
#include "material.h"
#include "hittable_internal.h"

/* 
	The ultimate goal is to find the normal vector of the surface.(outward_norm)
	An outward_norm can be obtained in the following way.
	  The point h is the apex.
	  The point p is the intersection point.
	  We'll find a point q on the axis,
	  where vector pq and vector ph are perpendicular. 

	Line by axis: C_point + t * axis_vec (different from ray)
	   The given point C is the center of the disk.

	We need to calculate the value of 't' to find point q. 
	Equation system: 
	  (Q - P) * PH_vec = 0
	  (C + t * dir_vec - P) * PH_vec = 0
	Solution:
	   t = cp_vec * ph_vec / axis_vec *  ph_vec
	So, the vector qp is the outward_norm. (That's what we want!)
*/
static void	conical_hat_record_set_normal_and_face(t_hittable_conical_hat *hat,
													t_hit_record *rec,
													const t_ray *ray)
{
	t_vec3	cp;
	t_vec3	ph;
	double	t;
	t_point	q;
	t_vec3	outward_norm;

	vec3_sub_vec3(&cp, &rec->p, &hat->center_of_disk);
	vec3_sub_vec3(&ph, &hat->apex, &rec->p);
	t = vec3_dot_vec3(&cp, &ph) \
					/ vec3_dot_vec3(&ray->dir, &ph);
	vec3_mult_num(&q, &hat->axis, t);
	vec3_add_vec3_inplace(&q, &hat->center_of_disk);
	vec3_sub_vec3(&outward_norm, &rec->p, &q);
	vec3_unitize(&outward_norm);
	hit_record_set_normal_and_face(rec, ray, &outward_norm);
}

/* 
	Reference: http://www.illusioncatalyst.com/notes_files/mathematics
			  /line_cone_intersection.php

	Cone: |P - H|^2 - [(P - H) * axis_vec]^2 = m *[(P - H) * axis_vec]^2
	   The trace of P represents a cone. (the sides of a cone, to be precise)
	   The point H is the apex of the cone.
	   The constant m: m = radius^2 / height^2
	Line: A_point + t * dir_vec
	   The given point A is origin of the line,
	   The vector dir is direction vector of line 

	By aligning a cone and a line,
	the following quadratic equation for 't' can be obtained. 
	at^2 + 2bt + c = 0, where
	a = dir * dir - m(dir * axis)^2 - (dir * axis)^2,
	b = 2 * [(dir * w) - m(dir * axis)(w * axis) - (dir * axis)(w * axis)],
	c = w * w - m(w * axis)^2 - (w * axis)^2

	w vector is A - H (i.e vector ha).
*/
static void	set_coefficient(double coef[3],
							t_hittable_conical_hat *hat,
							const t_ray *ray)
{
	const double	m = pow(hat->radius, 2) / pow(hat->height, 2);
	t_vec3			ha;

	vec3_sub_vec3(&ha, &ray->orig, &hat->apex);
	coef[A] = vec3_dot_vec3(&ray->dir, &ray->dir) \
				- m * pow(vec3_dot_vec3(&ray->dir, &hat->axis), 2) \
				- pow(vec3_dot_vec3(&ray->dir, &hat->axis), 2);
	coef[B] = vec3_dot_vec3(&ray->dir, &ha) \
											\
				- (m * vec3_dot_vec3(&ray->dir, &hat->axis) \
											* vec3_dot_vec3(&ha, &hat->axis)) \
																			\
				- (vec3_dot_vec3(&ray->dir, &hat->axis) \
											* vec3_dot_vec3(&ha, &hat->axis));
	coef[B] *= 2;
	coef[C] = vec3_dot_vec3(&ha, &ha) \
				- m * pow(vec3_dot_vec3(&ha, &hat->axis), 2) \
				- pow(vec3_dot_vec3(&ha, &hat->axis), 2);
}


static t_bool	root_is_out_of_range(t_hittable_conical_hat *hat,
										t_hit_record *rec)
{
	t_vec3	ch;
	t_vec3	cp;
	double	ch_dot_cp;

	vec3_sub_vec3(&ch, &hat->apex, &hat->center_of_disk);
	vec3_sub_vec3(&cp, &rec->p, &hat->center_of_disk);

	ch_dot_cp = vec3_dot_vec3(&ch, &cp);
	if (ch_dot_cp > pow(hat->height, 2) || ch_dot_cp < 0)
		return (TRUE);
	return (FALSE);
}

// TODO: 법선에 수직인 경우(중근), 예외처리 추가
// TODO: root_is_out_of_range 필요시 추가
// TODO: implement u/v calculation
/*
	This function needs to solve equation system of cone and straight line.
	We can get quadratic equation for 't' by aligning this equation system.
	See the comment of the set_coefficient for details.
*/
t_bool	hit_conical_hat(t_hittable *hittable,
						const t_ray *ray,
						t_minmax t,
						t_hit_record *rec)
{
	t_hittable_conical_hat	*this;
	double					coef[3];
	double					root;

	this = (t_hittable_conical_hat *)hittable;
	set_coefficient(coef, this, ray);
	if (solver_quadratic_equation(t, coef, &root) == FALSE)
		return (FALSE);
	rec->t = root;
	ray_at(&rec->p, ray, rec->t);
	if (root_is_out_of_range(this, rec))
		return (FALSE);
	rec->material = this->material;
	conical_hat_record_set_normal_and_face(this, rec, ray);
	if (fabs(vec3_dot_vec3(&rec->normal, &ray->dir)) < DOUBLE_E)
		return (FALSE);
	vec2_setval(&rec->uv, 0, 0);
	return (TRUE);
}
