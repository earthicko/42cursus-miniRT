#include <stdio.h>
#include <stdlib.h>
#include "hittable_bonus.h"

void	setinfo(t_cylinder_info *info)
{
	vec3_setval(&info->axis, 0.707106781, 0.707106781, 0);
	vec3_setval(&info->center, 0, 0, 0);
	info->height = 20;
	info->radius = 10;
}

void	create(t_hittable **cylinder, t_hittable **transform)
{
	t_cylinder_info	info;
	t_point			sp_orig;
	t_point			orig;

	setinfo(&info);
	vec3_setval(&sp_orig, 0, 0, 0);
	vec3_setval(&orig, 0, 0, 0);
	*cylinder = hittable_cylinder_create(&info, NULL);
	*transform = hittable_transform_create(*cylinder, orig, 30, 0);
}

int	main(void)
{
	t_hittable		*cylinder;
	t_hittable		*transform;
	t_ray			ray;
	t_minmax		t;
	t_hit_record	rec;

	create(&cylinder, &transform);
	vec3_setval(&ray.dir, 0, 0, -1);
	vec3_setval(&ray.orig, 0, 0, 20);
	t.min = 0.001;
	t.max = 99999999999;
	transform->hit(transform, &ray, t, &rec);
	return (0);
}
