#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "material.h"
#include "geometry.h"
#include "hittable_internal.h"


// TODO: hit 함수 구현.. 핵심

typedef struct s_cylinder_info
{
	t_point	center;
	t_vec3	axis;
	double	height;
	double	radius;
}	t_cylinder_info;

t_bool	hit_cylinder(t_hittable *hittable,
					t_ray *ray,
					t_minmax t,
					t_hit_record *rec)
{
	t_hittable_cylinder	*this;
	t_vec3				outward_norm;
}

static t_bool	root_is_out_of_range(t_hittable_tube *tube, t_hit_record *rec)
{
	double	max_dist_sq;

	max_dist_sq = pow(tube->height / 2, 2) + pow(tube->radius, 2);
	if (dist_sq(&rec->p, &tube->center_of_cylinder) > max_dist_sq)
		return (FALSE);
	return (TRUE);
}


// TODO: 렌더링시, axis 방향에 영향이 있는지 꼭 체크, axis에 -1 실수배 해볼 것
// http://www.illusioncatalyst.com/notes_files/mathematics/line_cylinder_intersection.php
t_bool	hit_tube(t_hittable *hittable,
					t_ray *ray,
					t_minmax t,
					t_hit_record *rec)
{
	t_hittable_tube	*this;
	t_vec3			ca;
	t_vec3			outward_norm;
	double			coef[3];
	double			root;

	this = (t_hittable_tube *)hittable;
	vec3_sub_vec3(&ca, &ray->orig, &this->center_of_cylinder);
	coef[A] = vec3_dot_vec3(&ray->dir, &ray->dir) \
				- pow(vec3_dot_vec3(&ray->dir, &this->axis), 2);
	coef[B] = 2 * (vec3_dot_vec3(&ray->dir, &ca) \
					- (vec3_dot_vec3(&ray->dir, &this->axis) \
						* vec3_dot_vec3(&ca, &this->axis)));
	coef[C] = vec3_dot_vec3(&ca, &ca) - pow(vec3_dot_vec3(&ca, &ray->dir), 2) \
				- pow(this->radius, 2);
	if (solve_quadratic_equation(t, coef, &root) == FALSE)
		return (FALSE);
	rec->t = root;
	ray_at(&rec->p, ray, rec->t);
	if (root_is_out_of_range(this, rec))
		return (FALSE);
}

// TODO: 반드시 shift와 shift_inverse의 렌더링 결과를 비교할 것
static void	set_tube_of_cylinder(t_hittable_tube *tube,
									t_cylinder_info *cylinder_info,
									t_material *material)
{
	t_point	center_of_disk;
	t_vec3	shift;

	tube->center_of_base = cylinder_info->center;
	vec3_mult_num(&shift, &cylinder_info->axis, cylinder_info->height / 2);
	vec3_add_vec3_inplace(&tube->center_of_base, &shift);
	tube->hit = hit_tube;
	tube->material = material;
	tube->center_of_cylinder = cylinder_info->center;
	tube->axis = cylinder_info->axis;
	tube->height = cylinder_info->height;
	tube->radius = cylinder_info->radius;
}

// TODO: wgcc에서 shift 초기화 안해서 에러뱉을수도
static void	set_disk_of_cylinder(t_hittable_disk *disk,
									t_cylinder_info *cylinder_info,
									t_material *material,
									int disk_type)
{
	t_vec3	axis_inverse;
	t_vec3	shift;

	disk->hit = hit_disk;
	disk->material = material;
	ft_memset(&disk->plane, 0, sizeof(t_hittable_plane));
	if (disk_type == TOP)
		vec3_mult_num(&shift, &cylinder_info->axis, cylinder_info->height / 2);
	else if (disk_type == BOTTOM)
	{
		vec3_mult_num(&axis_inverse, &cylinder_info->axis, -1);
		vec3_mult_num(&shift, &axis_inverse, cylinder_info->height / 2);
	}
	disk->plane.point = cylinder_info->center;
	vec3_add_vec3_inplace(&disk->plane.point, &shift);
	disk->plane.norm = cylinder_info->axis;
	disk->radius = cylinder_info->radius;
}

/*
static int	cylinder_destructor(t_hittable_cylinder *cylinder, int err_code)
{
	free(cylinder->disk[0]);
	free(cylinder->disk[1]);
	free(cylinder->tube);
	free(cylinder);
	return (err_code);
}
*/

/*
static int	init_cylinder_and_elements(t_hittable_cylinder **cylinder,
										t_cylinder_info *cylinder_info,
										t_material *material)
{
	*cylinder = malloc(sizeof(t_hittable_cylinder));
	if (!*cylinder)
		return (CODE_ERROR_MALLOC);
	ft_memset(*cylinder, 0, sizeof(t_hittable_cylinder));
	cylinder->tube = malloc(sizeof(t_hittable_tube));
	cylinder->disk[0] = malloc(sizeof(t_hittable_disk));
	cylinder->disk[1] = malloc(sizeof(t_hittable_disk));
	if (!cylinder->tube || !cylinder->disk[0] || !cylinder->disk[1])
		return (cylinder_destructor(*cylinder, CODE_ERROR_MALLOC));
	ft_memset(cylinder->tube, 0, sizeof(t_hittable_tube));
	ft_memset(cylinder->disk[0], 0, sizeof(t_hittable_disk));
	ft_memset(cylinder->disk[1], 0, sizeof(t_hittable_disk));
	set_tube_of_cylinder(*cylinder->tube, cylinder_info, material);
	set_disk_of_cylinder(*cylinder->disk[0], cylinder_info, material, BOTTOM);
	set_disk_of_cylinder(*cylinder->disk[1], cylinder_info, material, TOP);
	return (CODE_OK);
}
*/

t_hittable_cylinder	*cylinder_create(t_cylinder_info *cylinder_info,
										t_material *material)
{
	t_hittable_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_hittable_cylinder));
	if (!cylinder)
		return (CODE_ERROR_MALLOC);
	ft_memset(cylinder, 0, sizeof(t_hittable_cylinder));
	set_tube_of_cylinder(&cylinder->tube, cylinder_info, material);
	set_disk_of_cylinder(&cylinder->disk[0], cylinder_info, material, BOTTOM);
	set_disk_of_cylinder(&cylinder->disk[1], cylinder_info, material, TOP);
	/*
	if (init_cylinder_and_elements(&cylinder, cylinder_info, material)
		== CODE_ERROR_MALLOC)
		return (NULL);
	*/
}