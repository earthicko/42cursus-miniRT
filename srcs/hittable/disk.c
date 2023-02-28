#include <math.h>
#include "libft.h"
#include "material.h"
#include "geometry.h"
#include "hittable_internal.h"

static t_bool	root_is_out_of_range(t_hittable_disk *disk, t_hit_record *rec)
{
	if (dist_sq(&rec->p, &disk->plane.point) > pow(disk->radius, 2))
		return (TRUE);
	return (FALSE);
}

t_bool	hit_disk(t_hittable *hittable,
					const t_ray *ray,
					t_minmax t,
					t_hit_record *rec)
{
	t_hittable_disk	*this;
	t_vec3			outward_norm;
	double			root;

	this = (t_hittable_disk *)hittable;
	if (solve_equation_system_plane_and_line(t, &this->plane, ray, &root)
		== FALSE)
		return (FALSE);
	rec->t = root;
	ray_at(&rec->p, ray, rec->t);
	if (root_is_out_of_range(this, rec))
		return (FALSE);
	rec->material = this->material;
	outward_norm = this->plane.norm;
	hit_record_set_normal_and_face(rec, ray, &outward_norm);
	return (TRUE);
}

// TODO: wgcc에서 shift 초기화 안해서 에러뱉을수도
void	set_disk_of_cylinder(t_hittable_disk *disk,
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


void	set_disk_of_cone(t_hittable_disk *disk,
							t_cone_info *cone_info,
							t_material *material)
{
	disk->hit = hit_disk;
	disk->material = material;
	ft_memset(&disk->plane, 0, sizeof(t_hittable_plane));
	disk->plane.point = cone_info->center_of_disk;
	disk->plane.norm = cone_info->axis;
	disk->radius = cone_info->radius;
}