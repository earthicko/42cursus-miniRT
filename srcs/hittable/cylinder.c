#include <stdlib.h>
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

static void	set_tube_of_cylinder(t_hittable_tube *tube,
									t_cylinder_info *cylinder_info,
									t_material *material)
{
	tube->hit = hit_tube;
	tube->material = material;
	tube->center = cylinder_info->center;
	tube->axis = cylinder_info->axis;
	tube->height = cylinder_info->height;
	tube->radius = cylinder_info->radius;
}

static void	set_disk_of_cylinder(t_hittable_disk *disk,
									t_cylinder_info *cylinder_info,
									t_material *material,
									int disk_type)
{
	t_vec3	shift;

	disk->hit = hit_disk;
	disk->material = material;
	ft_memset(&disk->plane, 0, sizeof(t_hittable_plane));
	disk->plane.point = cylinder_info->center;
	if (disk_type == TOP)
	{
		vec3_mult_num(&shift, &cylinder_info->axis, cylinder_info->height);
		vec3_add_vec3_inplace(&disk->plane.point, &shift);
	}
	disk->plane.norm = cylinder_info->axis;
	disk->radius = cylinder_info->radius;
}

static int	cylinder_destructor(t_hittable_cylinder *cylinder, int err_code)
{
	free(cylinder->disk[0]);
	free(cylinder->disk[1]);
	free(cylinder->tube);
	free(cylinder);
	return (err_code);
}

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

t_hittable_cylinder	*cylinder_create(t_cylinder_info *cylinder_info,
										t_material *material)
{
	t_hittable_cylinder	*cylinder;

	if (init_cylinder_and_elements(&cylinder, cylinder_info, material)
		== CODE_ERROR_MALLOC)
		return (NULL);
}