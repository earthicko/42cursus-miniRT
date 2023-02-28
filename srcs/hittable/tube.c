#include <math.h>
#include "libft.h"
#include "material.h"
#include "geometry.h"
#include "hittable_internal.h"

static t_bool	root_is_out_of_range(t_hittable_tube *tube, t_hit_record *rec)
{
	double	max_dist_sq;

	max_dist_sq = pow(tube->height / 2, 2) + pow(tube->radius, 2);
	if (dist_sq(&rec->p, &tube->center_of_cylinder) > max_dist_sq)
		return (TRUE);
	return (FALSE);
}

/*
	This function should find Point q, that is on axis 
	and following following condition is met.

	Point P is hit point
	Point Q is on the axis. PQ_vec * axis_vec = 0 (Perpendicular)

	Line by axis: C_point + t * axis_vec (different from ray)
				  The given point C is the center of the disk.
	
	Equation system:
	(Q - P) * axis_vec = 0
	(C + t * axis_vec - P) * axis_vec = 0;
	t= (P - C) * axis_vec / axis_vec * axis_vec 
	
*/
static void	tube_hit_record_set_normal_and_face(t_hittable_tube *tube,
											t_hit_record *rec,
											const t_ray *ray)
{
	t_vec3	cp;
	double	t;
	t_point	q;
	t_point	outward_norm;

	vec3_sub_vec3(&cp, &rec->p, &tube->center_of_disk);
	t = vec3_dot_vec3(&cp, &tube->axis) \
		/ vec3_dot_vec3(&tube->axis, &tube->axis);
	vec3_mult_num(&q, &tube->axis, t);
	vec3_add_vec3_inplace(&q, &tube->center_of_disk);
	vec3_sub_vec3(&outward_norm, &rec->p, &q);
	vec3_unitize(&outward_norm);
	hit_record_set_normal_and_face(rec, ray, &outward_norm);
}

static void	set_coefficient(double coef[3],
								t_hittable_tube *tube,
								const t_ray *ray,
								t_vec3 *ca)
{
	coef[A] = vec3_dot_vec3(&ray->dir, &ray->dir) \
				- pow(vec3_dot_vec3(&ray->dir, &tube->axis), 2);
	coef[B] = 2 * (vec3_dot_vec3(&ray->dir, ca) \
					- (vec3_dot_vec3(&ray->dir, &tube->axis) \
						* vec3_dot_vec3(ca, &tube->axis)));
	coef[C] = vec3_dot_vec3(ca, ca) \
				- pow(vec3_dot_vec3(ca, &tube->axis), 2) \
				- pow(tube->radius, 2);
}

// Reference: http://www.illusioncatalyst.com/notes_files/mathematics
//  		/line_cylinder_intersection.php
/*

	Point C is the center of the disk

	Line: A_point + t * dir_vec
	   The given point A is origin of the line,
	   The vector dir is direction vector of line 

	reference's w_vec is ca vector
*/

// TODO: ray_and_norm_are_perpendicular 함수 따로 뺄 것
// TODO: 다른 객체들은 충돌시키기 전에 수직인지 미리 아는 방법이 없기에 교점 구한 후 확인
t_bool	hit_tube(t_hittable *hittable,
					const t_ray *ray,
					t_minmax t,
					t_hit_record *rec)
{
	t_hittable_tube	*this;
	t_vec3			dir_cross_axis;
	t_vec3			ca;
	double			coef[3];
	double			root;

	this = (t_hittable_tube *)hittable;
	vec3_cross_vec3(&dir_cross_axis, &ray->dir, &this->axis);
	if (vec3_is_near_zero(&dir_cross_axis))
		return (FALSE);
	vec3_sub_vec3(&ca, &ray->orig, &this->center_of_disk);
	set_coefficient(coef, this, ray, &ca);
	if (solve_quadratic_equation(t, coef, &root) == FALSE)
		return (FALSE);
	rec->t = root;
	ray_at(&rec->p, ray, rec->t);
	rec->is_front = TRUE;
	if (root_is_out_of_range(this, rec))
		return (FALSE);
	rec->material = this->material;
	tube_hit_record_set_normal_and_face(this, rec, ray);
	return (TRUE);
}

void	set_tube_of_cylinder(t_hittable_tube *tube,
									t_cylinder_info *cylinder_info,
									t_material *material)
{
	t_vec3	shift;

	tube->center_of_disk = cylinder_info->center;
	vec3_mult_num(&shift, &cylinder_info->axis, cylinder_info->height / 2);
	vec3_add_vec3_inplace(&tube->center_of_disk, &shift);
	tube->hit = hit_tube;
	tube->material = material;
	tube->center_of_cylinder = cylinder_info->center;
	tube->axis = cylinder_info->axis;
	tube->height = cylinder_info->height;
	tube->radius = cylinder_info->radius;
}
