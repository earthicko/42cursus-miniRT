#include <stdio.h>
#include "hittable_bonus.h"
#include "print_bonus.h"

void	test_sphere(void)
{
	t_hittable	*sphere;
	t_point		point;

	vec3_setval(&point, 0, 0, 0);
	sphere = hittable_sphere_create(point, 1, 0);
}

void	test_plane(void)
{
	t_hittable	*plane;
	t_point		point;
	t_point		norm;

	vec3_setval(&point, 0, 0, 0);
	vec3_setval(&norm, 0, 0, 1);
	plane = hittable_plane_create(point, norm, 0);
}

void	test_cylinder(void)
{
	t_hittable		*cylinder;
	t_cylinder_info	info;
	t_point			point;
	t_point			norm;

	vec3_setval(&point, 0, 0, 0);
	vec3_setval(&norm, 0, 0, 1);
	info.axis = norm;
	info.height = 10;
	info.radius = 5;
	info.center_of_cylinder = point;
	cylinder = hittable_cylinder_create(&info, 0);
}

void	test_rect(void)
{
	t_hittable			*rect;
	t_aa_rectangle_info	info;
	t_ray				ray;
	t_minmax			t;
	t_hit_record		rec;

	info.axis = AXIS_Y;
	info.offset = 0;
	info.range[0].min = -10;
	info.range[0].max = 10;
	info.range[1].min = -20;
	info.range[1].max = 15;
	rect = hittable_aa_rectangle_create(info, 0);
	print_bbox(&rect->bbox);
	printf("\n");
	vec3_setval(&ray.dir, 0, 0, -1);
	vec3_setval(&ray.orig, 0, 10.00001, 10);
	t.min = DOUBLE_E;
	t.max = DOUBLE_INF;
	printf("hit: %d\n", rect->hit(rect, &ray, t, &rec));
	printf("hit point: ");
	print_vec3(&rec.p);
	printf("\nhit uv: ");
	print_vec2(&rec.uv);
	printf("\n");
}

int	main(void)
{
	test_sphere();
	test_plane();
	test_cylinder();
	test_rect();
	return (0);
}
