#include <stdio.h>
#include "print.h"


#include <math.h>
#include "libft.h"
#include "material.h"
#include "geometry.h"
#include "hittable_internal.h"

static t_bool	root_is_out_of_range(t_hittable_tube *tube, t_hit_record *rec)
{
	double	max_dist_sq;

	max_dist_sq = pow(tube->height / 2, 2) + pow(tube->radius, 2);
	// printf("max_dist_sq: %.2f\n", max_dist_sq);
	// printf("dist p to center_of_cylinder: %.2f\n", dist_sq(&rec->p, &tube->center_of_cylinder));
	if (dist_sq(&rec->p, &tube->center_of_cylinder) > max_dist_sq)
		return (TRUE);
	ft_printf("tube root is in range\n");
	return (FALSE);
}

static void	tube_hit_record_set_normal_and_face(const t_hittable_tube *tube,
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
	// printf("outward norm: ");
	// print_vec3(&outward_norm);
	// printf("  ");
	//print_hit_record(rec);
	//printf("\n\n");
	vec3_unitize(&outward_norm);
	hit_record_set_normal_and_face(rec, ray, &outward_norm);
}

// TODO: 렌더링시, axis 방향에 영향이 있는지 꼭 체크, axis에 -1 실수배 해볼 것
// URL: http://www.illusioncatalyst.com/notes_files/mathematics
//  	/line_cylinder_intersection.php
t_bool	hit_tube(t_hittable *hittable,
					const t_ray *ray,
					t_minmax t,
					t_hit_record *rec)
{
	t_hittable_tube	*this;
	t_vec3			ca;
	double			coef[3];
	double			root;

	this = (t_hittable_tube *)hittable;
	vec3_sub_vec3(&ca, &ray->orig, &this->center_of_disk);
	coef[A] = vec3_dot_vec3(&ray->dir, &ray->dir) \
				- pow(vec3_dot_vec3(&ray->dir, &this->axis), 2);
	coef[B] = 2 * (vec3_dot_vec3(&ray->dir, &ca) \
					- (vec3_dot_vec3(&ray->dir, &this->axis) \
						* vec3_dot_vec3(&ca, &this->axis)));
	coef[C] = vec3_dot_vec3(&ca, &ca) - pow(vec3_dot_vec3(&ca, &ray->dir), 2) \
				- pow(this->radius, 2);
	
	// 아니 대체 왜 ray만 두번 프린트되는거지 밑에 hit_record는 왜 프린트 안되지? 
	// equation이 false일 수가 있나? 말이 되냐고
	print_ray(ray);
	//printf("\n");
	printf("\n");
	//printf("(A, B, C) is (%.2f, %.2f, %.2f)\n", coef[A], coef[B], coef[C]);
	if (solve_quadratic_equation(t, coef, &root) == FALSE)
		return (FALSE);
	rec->t = root;
	ray_at(&rec->p, ray, rec->t);
	rec->is_front = TRUE;
	print_hit_record(rec);
	printf("\n\n");
	if (root_is_out_of_range(this, rec))
		return (FALSE);
	rec->material = this->material;
	tube_hit_record_set_normal_and_face(this, rec, ray);
	return (TRUE);
}

// TODO: 반드시 shift와 shift_inverse의 렌더링 결과를 비교할 것
//    (두 밑면의 중심중 어느것을 택해도 렌더링 결과가 같은지 확인)
//    실제로 center_of_disk는 두가지 경우가 존재
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
