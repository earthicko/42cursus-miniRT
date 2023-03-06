#include <math.h>
#include "hittable_bonus.h"
#include "geometry_bonus.h"

static void	set_r_axis_vec(t_vec3 *r_axis, t_vec3 *axis)
{
	const t_vec3	x_axis = {1, 0, 0};
	const t_vec3	y_axis = {0, 1, 0};

	if (fabs(axis->i[0]) > 0.9)
		vec3_cross_vec3(r_axis, &y_axis, axis);
	else
		vec3_cross_vec3(r_axis, &x_axis, axis);
	vec3_unitize(r_axis);
}

/*
	(x, y, z) is origin coordinates system. 
	(r, s, t) is cylindrical coordinate system.
	We'll map (x, y, z) -> (r, s, t)
	Also, the value t is the height in the cylindrical coordinate system.

	uv mapping:
	u: [0, 2pi] -> [0, 1]
	v: [0, height] -> [0, 1]
	u is a regular angle between r_axis and outward_norm. (0~2pi)
	v is a height of P in the cylindrical coordinate system. (0~height)
*/
void	tube_set_uv(t_hittable_tube *tube, t_hit_record *rec)
{
	t_vec3			cp;
	double			t;
	t_vec3			r_axis;
	t_vec3			r_axis_reversed;
	t_vec3			s_axis;

	vec3_sub_vec3(&cp, &rec->p, &tube->center_of_disk);
	t = vec3_dot_vec3(&cp, &tube->axis) \
					/ vec3_dot_vec3(&tube->axis, &tube->axis);
	set_r_axis_vec(&r_axis, &tube->axis);
	vec3_mult_num(&r_axis_reversed, &r_axis, -1);
	vec3_cross_vec3(&s_axis, &r_axis, &tube->axis);
	vec3_unitize(&s_axis);
	if (vec3_dot_vec3(&s_axis, &rec->normal) > 0)
		rec->uv.i[0] = acos(vec3_dot_vec3(&r_axis, &rec->normal)) / (2 * M_PI);
	else
		rec->uv.i[0] = (M_PI \
						+ acos(vec3_dot_vec3(&r_axis_reversed, &rec->normal))) \
																			\
																/ (2 * M_PI);
	rec->uv.i[1] = -t / tube->height;
}
