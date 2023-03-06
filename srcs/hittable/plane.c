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
	const t_vec3	x_axis = {{1, 0, 0}};
	const t_vec3	y_axis = {{0, 1, 0}};

	if (fabs(norm->i[0]) > 0.9)
		vec3_cross_vec3(u_axis, &y_axis, norm);
	else
		vec3_cross_vec3(u_axis, &x_axis, norm);
	vec3_unitize(u_axis);
}

/* 
	There is two way to do uv-mapping to make checker texture.

	1. Use decimal fraction. 
	   (This case uv will be mapped between 0 and 1.)
	2. Use the quotient of the coordinates divided by the length of the box.
	   (This does not necessarily require u,v to be mapped between 0 and 1.)
	   (In addition, proper multiplication of vectors must be performed 
	   to adjust the checkerboard spacing.)

	Why the way 2 can be appiled?: 
	The oddness of the quotient of coordinate divided by box length
	determines the texture of the coordinates.
	
	We'll chose the way 1.

	Initial box size: 1 / freq
	Box size after vector real multiplication operation: 
	Initial box size / t ---> 1 / (freq * t)
	
	The point O is origin in new u-v coordinates system.
	This is how the way 2 works.

	rec->uv.i[0] = fabs(floor(u_on)) / 10;
	rec->uv.i[1] = fabs(floor(v_on)) / 10; 

	10 is might be the length of the box.
	The scale of plane should be the same as freq of uv texture.
*/
static void	plane_set_uv(t_hittable_plane *plane, t_hit_record *rec)
{
	t_vec3	u_axis;
	t_vec3	v_axis;
	t_vec3	op;
	double	u_on;
	double	v_on;

	set_u_axis_vec(&u_axis, &rec->normal);
	vec3_cross_vec3(&v_axis, &u_axis, &rec->normal);
	vec3_unitize(&v_axis);
	vec3_sub_vec3(&op, &rec->p, &plane->point);
	u_on = vec3_dot_vec3(&op, &u_axis) / plane->scale;
	v_on = vec3_dot_vec3(&op, &v_axis) / plane->scale;
	u_on = fmod(u_on, 1);
	v_on = fmod(v_on, 1);
	if (u_on < 0)
		u_on += 1.0;
	if (v_on < 0)
		v_on += 1.0;
	vec2_setval(&rec->uv, u_on, v_on);
}

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
