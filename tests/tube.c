#include <stdio.h>
#include "hittable.h"
#include "ray.h"
#include "print.h"

t_bool	hit_tube(t_hittable *hittable,
					const t_ray *ray,
					t_minmax t,
					t_hit_record *rec);

static void	init_cylinder_info(t_cylinder_info *info,
								t_point center,
								t_vec3 axis,
								double h,
								double r)
{
	info->center_of_cylinder = center;
	info->axis = axis;
	info->height = h;
	info->radius = r;
}

int	main(void)
{
	t_hittable_cylinder	*cy;
	t_cylinder_info		info;
	t_hit_record		rec;
	t_ray				ray;

	init_cylinder_info(&info, (t_point){0, 0, 0}, (t_vec3){0, 0, 1}, \
						10, 5);
	cy = hittable_cylinder_create(&info, 0);
	ray.dir = (t_vec3){-10, 0, 5};
	ray.orig = (t_point){10, 0, 0};
	/****************/
	rec.p = (t_point){-100, -100, -100};
	rec.normal = (t_vec3){-100, -100, -100};
	// printf("(%f, %f, %f)\n", rec.p.i[0], rec.p.i[1], rec.p.i[2]);
	// print_hit_record(&rec);
	// printf("\n\n");
	rec.is_front = -100;
	/********************/
	printf("is hit?: %d\n\n", hit_tube((t_hittable *)&(cy->tube), &ray, (t_minmax){0.00001, 10000000}, &rec));
	print_hit_record(&rec);
}