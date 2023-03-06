#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "number.h"
#include "print.h"
#include "builder_internal.h"

static int	add_sphere(t_scene *scene, t_point cen, double d, t_material *m)
{
	t_hittable	*sphere;

	sphere = hittable_sphere_create(cen, d / 2, m);
	if (!sphere)
		return (CODE_ERROR_MALLOC);
	if (ptrarr_append(scene->res.primitives, sphere))
	{
		free(sphere);
		return (CODE_ERROR_MALLOC);
	}
	if (hittable_list_append(scene->world, sphere)
		|| hittable_list_append(scene->objects, sphere))
		return (CODE_ERROR_MALLOC);
	return (CODE_OK);
}

int	build_sphere(const t_ptrarr *tokens, t_scene *scene)
{
	t_point		cen;
	double		d;
	t_color		color;

	build_vector(&cen, &tokens->data[1]);
	d = ft_atof(tokens->data[6]);
	build_vector(&color, &tokens->data[7]);
	if (is_invalid_length(d / 2) || is_invalid_color(&color))
		return (CODE_ERROR_DATA);
	map_color(&color);
	if (add_texture_solid(scene, "", color))
		return (CODE_ERROR_MALLOC);
	if (add_material_lambertian(scene, "", ptrarr_getlast(scene->res.textures)))
		return (CODE_ERROR_MALLOC);
	if (add_sphere(scene, cen, d, ptrarr_getlast(scene->res.materials)))
		return (CODE_ERROR_MALLOC);
	printf("%s: sphere (center ", __func__);
	print_vec3(&cen);
	printf(", radius %.2f, color ", d / 2);
	print_vec3(&color);
	printf(")\n");
	return (CODE_OK);
}
