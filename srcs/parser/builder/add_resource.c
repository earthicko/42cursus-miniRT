#include <stdlib.h>
#include "geometry.h"
#include "scene.h"

int	add_texture_solid(t_scene *scene, const char *name, t_color color)
{
	t_texture	*solid;

	solid = texture_solid_create(name, color);
	if (!solid)
		return (CODE_ERROR_MALLOC);
	if (ptrarr_append(scene->res.textures, solid))
	{
		texture_destroy(solid);
		return (CODE_ERROR_MALLOC);
	}
	return (CODE_OK);
}

int	add_material_lambertian(t_scene *scene,
		const char *name, t_texture *texture)
{
	t_material	*lambertian;

	lambertian = material_lambertian_create(name, texture);
	if (!lambertian)
		return (CODE_ERROR_MALLOC);
	if (ptrarr_append(scene->res.materials, lambertian))
	{
		free(lambertian);
		return (CODE_ERROR_MALLOC);
	}
	return (CODE_OK);
}
