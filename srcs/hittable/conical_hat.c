#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "geometry.h"
#include "number.h"
#include "material.h"
#include "hittable_internal.h"

// outward_norm
// norm: 1. Pass through point p and perpendicular to vector ph (h is apex) 
//		 2. norm should pass through one point on aixs
static void	conical_hat_record_set_normal_and_face(t_hittable_conical_hat *hat,
													t_hit_record *rec,
													const t_ray *ray)
{
	t_vec3	outward_norm;
}

// Reference: http://www.illusioncatalyst.com/notes_files/mathematics
// 			/line_cone_intersection.php
/*
	Point H is apex of cone
	
	Line: A_point + t * dir_vec
	   The given point A is origin of the line,
	   The vector dir is direction vector of line 

	m = radius^2 / height^2

	w vector is ha
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
				- pow(vec3_dot_vec3(&ha, &hat->axis), 2) \
				- pow(vec3_dot_vec3(&ha, &hat->axis), 2);

}

// TODO: 법선에 수직인 경우(중근), 예외처리 추가
// TODO: root_is_out_of_range 필요시 추가
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
	if (solve_quadratic_equation(t, coef, &root) == FALSE)
		return (FALSE);
	rec->t = root;
	ray_at(&rec->p, ray, rec->t);
	rec->material = this->material;
	conical_hat_record_set_normal_and_face(this, rec, ray);
	return (TRUE);
}

// shift: add shift to center_of_disk to get apex
void	set_conical_hat_of_cylinder(t_hittable_conical_hat *conical_hat,
									t_cone_info *cone_info,
									t_material *material)
{
	t_vec3	shift;


	conical_hat->hit = hit_conical_hat;
	conical_hat->material = material;
	conical_hat->apex = cone_info->center_of_disk;
	vec3_mult_num(&shift, &cone_info->axis, cone_info->height);
	vec3_add_vec3_inplace(&conical_hat->apex, &shift);
	conical_hat->center_of_disk = cone_info->center_of_disk;
	conical_hat->axis = cone_info->axis;
	conical_hat->height = cone_info->height;
	conical_hat->radius = cone_info->radius;
}
