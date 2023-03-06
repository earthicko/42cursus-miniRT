#include <stdio.h>
#include "hittable_bonus.h"
#include "ray_bonus.h"
#include "print_bonus.h"

t_bool	hit_cone(t_hittable *hittable,
					const t_ray *ray,
					t_minmax t,
					t_hit_record *rec);


t_bool	hit_conical_hat(t_hittable *hittable,
						const t_ray *ray,
						t_minmax t,
						t_hit_record *rec);

void	init_cone_info(t_cone_info *info, t_point cen, t_vec3 axis, \
						 double h, double r)
{
	info->center_of_disk = cen;
	info->axis = axis;
	info->height = h;
	info->radius = r;
}

int	main(void)
{
	t_hittable_cone	*cone;
	t_cone_info		info;
	t_hit_record	rec;
	t_ray			ray;

	init_cone_info(&info, (t_point){0, 0, 0}, (t_vec3){0, 0, 1}, 10, 10);
	cone = (t_hittable_cone *)hittable_cone_create(&info, 0);
	ray.dir = (t_vec3){-1, 0, 0};
	ray.orig = (t_point){10, 0, 5};
	/****************/
	rec.p = (t_point){-100, -100, -100};
	rec.normal = (t_vec3){-100, -100, -100};
	rec.is_front = -100;
	/********************/
	printf("is hit?: %d\n\n", hit_conical_hat((t_hittable *)&(cone->conical_hat), &ray, (t_minmax){-1, 10000000}, &rec));
	print_hit_record(&rec);
}