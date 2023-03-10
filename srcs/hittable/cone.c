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
t_bool	hit_cone(t_hittable *hittable,
					const t_ray *ray,
					t_minmax t,
					t_hit_record *rec)
{
	t_hit_record		rec_buf;
	t_bool				hit_anything;
	int					i;
	const t_hittable	*targets[2] = {
		(t_hittable *)(&((t_hittable_cone *)hittable)->conical_hat),
		(t_hittable *)(&((t_hittable_cone *)hittable)->disk),
	};

	hit_anything = FALSE;
	i = 0;
	while (i < 2)
	{
		if (targets[i]->hit((t_hittable *)targets[i], ray, t, &rec_buf))
		{
			hit_anything = TRUE;
			*rec = rec_buf;
			t.max = rec_buf.t;
		}
		i++;
	}
	return (hit_anything);
}

static void	set_disk_of_cone(t_hittable_disk *disk,
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

/*
	t_vec 3 shift: Add shift to center_of_disk to get apex point.
*/
static void	set_conical_hat_of_cone(t_hittable_conical_hat *conical_hat,
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

t_hittable	*hittable_cone_create(t_cone_info *cone_info,
									t_material *material)
{
	t_hittable_cone	*cone;

	cone = malloc(sizeof(t_hittable_cone));
	if (!cone)
		return (NULL);
	ft_memset(cone, 0, sizeof(t_hittable_cone));
	cone->destroy = hittable_destroy;
	cone->hit = hit_cone;
	cone->material = material;
	set_disk_of_cone(&cone->disk, cone_info, material);
	set_conical_hat_of_cone(&cone->conical_hat, cone_info, material);
	return ((t_hittable *)cone);
}
