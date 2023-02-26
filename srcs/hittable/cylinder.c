#include <stdio.h>


#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "geometry.h"
#include "number.h"
#include "material.h"
#include "hittable_internal.h"

t_bool	hit_cylinder(t_hittable *hittable,
					const t_ray *ray,
					t_minmax t,
					t_hit_record *rec)
{
	t_hittable_cylinder	*this;

	this = (t_hittable_cylinder *)hittable;
	if (this->tube.hit((t_hittable *)&this->tube, ray, t, rec))
	{
		ft_printf("hit tube\n");
		t.max = rec->t;
	}
	
	/*
	if (this->disk[0].hit((t_hittable *)&this->disk[0], ray, t, rec))
	{
		printf("hit disk[0]\n");
		t.max = rec->t;
	}
	if (this->disk[1].hit((t_hittable *)&this->disk[1], ray, t, rec))
	{
		printf("hit disk[1]\n");
		t.max = rec->t;
	}
	*/
	if (val_is_near_zero(t.max - DOUBLE_INF))
		return (FALSE);
	return (TRUE);
}

t_hittable_cylinder	*hittable_cylinder_create(t_cylinder_info *cylinder_info,
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
	return (cylinder);
}
