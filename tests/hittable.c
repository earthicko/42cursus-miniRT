#include "hittable.h"

int	main(void)
{
	t_hittable_sphere	*sphere;
	t_hittable_plane	*plane;
	t_hittable_cylinder	*cylinder;
	t_cylinder_info		info;
	t_point				point;
	t_point				norm;

	vec3_setval(&point, 0, 0, 0);
	sphere = hittable_sphere_create(point, 1, 0);
	(void)sphere;
	vec3_setval(&norm, 0, 0, 1);
	plane = hittable_plane_create(point, norm, 0);
	(void)plane;
	info.axis = norm;
	info.height = 10;
	info.radius = 5;
	info.center_of_cylinder = point;
	cylinder = hittable_cylinder_create(&info, 0);
	(void)cylinder;
	return (0);
}
