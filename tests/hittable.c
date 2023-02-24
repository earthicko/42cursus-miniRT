#include "hittable.h"

int	main(void)
{
	t_hittable_sphere	*sphere;
	t_point				point;

	vec3_setval(&point, 0, 0, 0);
	sphere = sphere_create(point, 1, 0);
	return (0);
}
