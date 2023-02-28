#include <math.h>
#include "libft.h"
#include "material.h"
#include "geometry.h"
#include "hittable_internal.h"


static t_bool	ray_and_outward_norm_perpendicular(const t_ray *ray,
													t_vec3 *axis)
{
	t_vec3	dir_cross_axis;

	vec3_cross_vec3(&dir_cross_axis, &ray->dir, axis);
	if (vec3_is_near_zero(&dir_cross_axis))
		return (TRUE);
	return (FALSE);
}

/*
	Reference: http://www.illusioncatalyst.com/notes_files/mathematics
				/line_cylinder_intersection.php

	Cylinder: |P - C|^2 -[(P-C) * axis_vec]^2 = r^2
	  The trace of P represents a cylinder. (the sides of cylinder, precisely)
	  The point C is the center of the disk.
	  The r is the radius of the cylinder.
	Line: A_point + t * dir_vec
	   The given point A is origin of the line,
	   The vector dir is direction vector of line 

	By aligning a cylinder and a line,
	the following quadratic equation for 't' can be obtained. 
	at^2 + 2bt + c = 0, where
	a = dir * dir - (dir * axis)^2,
	b = 2 * [dir * w - (dir * axis)(w * axis)],
	c = w * w - (w * axis)^2 - r^2

	w vector is A - C (i.e vector ca)
*/
static void	set_coefficient(double coef[3],
								t_hittable_tube *tube,
								const t_ray *ray)
{
	t_vec3	ca;

	vec3_sub_vec3(&ca, &ray->orig, &tube->center_of_disk);
	coef[A] = vec3_dot_vec3(&ray->dir, &ray->dir) \
				- pow(vec3_dot_vec3(&ray->dir, &tube->axis), 2);
	coef[B] = vec3_dot_vec3(&ray->dir, &ca) \
											\
				- (vec3_dot_vec3(&ray->dir, &tube->axis) \
								* vec3_dot_vec3(&ca, &tube->axis));
	coef[B] *= 2;
	coef[C] = vec3_dot_vec3(&ca, &ca) \
				- pow(vec3_dot_vec3(&ca, &tube->axis), 2) \
				- pow(tube->radius, 2);
}

static t_bool	root_is_out_of_range(t_hittable_tube *tube, t_hit_record *rec)
{
	double	max_dist_sq;

	max_dist_sq = pow(tube->height / 2, 2) + pow(tube->radius, 2);
	if (dist_sq(&rec->p, &tube->center_of_cylinder) > max_dist_sq)
		return (TRUE);
	return (FALSE);
}

/*
	The ultimate goal is to find the normal vector of the surface.(outward_norm)
	An outward_norm can be obtained in the following way.
	  The point p is the intersection point.
	  We'll find a point q on the axis,
	  where the pq_vec and the axis_vec are perpendicular. 

	Line by axis: C_point + t * axis_vec (different from ray)
	   The given point C is the center of the disk.

	We'll calculate the value of 't' to find point q. 
	Equation system:
	  (Q - P) * axis_vec = 0
	  (C + t * axis_vec - P) * axis_vec = 0
	Solution:
	  t= (P - C) * axis_vec / axis_vec * axis_vec 
	So, the vector qp is the outward_norm. (That's what we want!)
*/
static void	tube_hit_record_set_normal_and_face(t_hittable_tube *tube,
												t_hit_record *rec,
												const t_ray *ray)
{
	t_vec3	cp;
	double	t;
	t_point	q;
	t_vec3	outward_norm;

	vec3_sub_vec3(&cp, &rec->p, &tube->center_of_disk);
	t = vec3_dot_vec3(&cp, &tube->axis) \
					/ vec3_dot_vec3(&tube->axis, &tube->axis);
	vec3_mult_num(&q, &tube->axis, t);
	vec3_add_vec3_inplace(&q, &tube->center_of_disk);
	vec3_sub_vec3(&outward_norm, &rec->p, &q);
	vec3_unitize(&outward_norm);
	hit_record_set_normal_and_face(rec, ray, &outward_norm);
}

// TODO: ray_and_norm_are_perpendicular 함수 따로 뺄 것
// TODO: 다른 객체들은 충돌시키기 전에 수직인지 미리 아는 방법이 없기에 교점 구한 후 확인
/*
	This function needs to solve equation system of cylinder and straight line
	We can get quadratic equation for 't' by aligning this equation system.
	See the comment of the set_coefficient for details.
*/
t_bool	hit_tube(t_hittable *hittable,
					const t_ray *ray,
					t_minmax t,
					t_hit_record *rec)
{
	t_hittable_tube	*this;
	double			coef[3];
	double			root;

	this = (t_hittable_tube *)hittable;
	if (ray_and_outward_norm_perpendicular(ray, &this->axis))
		return (FALSE);
	set_coefficient(coef, this, ray);
	if (solver_quadratic_equation(t, coef, &root) == FALSE)
		return (FALSE);
	rec->t = root;
	ray_at(&rec->p, ray, rec->t);
	if (root_is_out_of_range(this, rec))
		return (FALSE);
	rec->material = this->material;
	tube_hit_record_set_normal_and_face(this, rec, ray);
	return (TRUE);
}
