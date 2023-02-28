#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "geometry.h"
#include "number.h"
#include "material.h"
#include "hittable_internal.h"

/*
	For details, see hit functions for each elements.
*/
t_bool	hit_cylinder(t_hittable *hittable,
						const t_ray *ray,
						t_minmax t,
						t_hit_record *rec)
{
	t_hittable_cylinder	*this;

	this = (t_hittable_cylinder *)hittable;
	if (this->tube.hit((t_hittable *)&this->tube, ray, t, rec))
		t.max = rec->t;
	if (this->disk[0].hit((t_hittable *)&this->disk[0], ray, t, rec))
		t.max = rec->t;
	if (this->disk[1].hit((t_hittable *)&this->disk[1], ray, t, rec))
		t.max = rec->t;
	if (fabs(t.max - DOUBLE_INF) < DOUBLE_E)
		return (FALSE);
	return (TRUE);
}

/*
	shift: Add shift to center_of_cylinder to get center_of_disk
*/
static void	set_tube_of_cylinder(t_hittable_tube *tube,
									t_cylinder_info *cylinder_info,
									t_material *material)
{
	t_vec3	shift;

	tube->hit = hit_tube;
	tube->material = material;
	tube->center_of_disk = cylinder_info->center_of_cylinder;
	vec3_mult_num(&shift, &cylinder_info->axis, cylinder_info->height / 2);
	vec3_add_vec3_inplace(&tube->center_of_disk, &shift);
	tube->center_of_cylinder = cylinder_info->center_of_cylinder;
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
	disk->plane.point = cylinder_info->center_of_cylinder;
	vec3_add_vec3_inplace(&disk->plane.point, &shift);
	disk->plane.norm = cylinder_info->axis;
	disk->radius = cylinder_info->radius;
}

t_hittable	*hittable_cylinder_create(t_cylinder_info *cylinder_info,
										t_material *material)
{
	t_hittable_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_hittable_cylinder));
	if (!cylinder)
		return (NULL);
	ft_memset(cylinder, 0, sizeof(t_hittable_cylinder));
	cylinder->hit = hit_cylinder;
	cylinder->material = material;
	set_tube_of_cylinder(&cylinder->tube, cylinder_info, material);
	set_disk_of_cylinder(&cylinder->disk[0], cylinder_info, material, BOTTOM);
	set_disk_of_cylinder(&cylinder->disk[1], cylinder_info, material, TOP);
	return ((t_hittable *)cylinder);
}
