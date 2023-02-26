#include <stdlib.h>
#include "libft.h"
#include "ptrarr.h"
#include "hittable.h"
#include "scene.h"

static t_bool	is_all_allocated(t_scene *scene)
{
	if (!(scene->res.primitives))
		return (FALSE);
	if (!(scene->res.materials))
		return (FALSE);
	if (!(scene->res.textures))
		return (FALSE);
	if (!(scene->world))
		return (FALSE);
	if (!(scene->objects))
		return (FALSE);
	return (TRUE);
}

void	scene_destroy(t_scene *scene)
{
	if (scene->res.primitives)
		ptrarr_destroy(scene->res.primitives, TRUE);
	if (scene->res.materials)
		ptrarr_destroy(scene->res.materials, TRUE);
	if (scene->res.textures)
		ptrarr_destroy(scene->res.textures, TRUE);
	if (scene->world)
		hittable_list_destroy((t_hittable_list *)scene->world);
	if (scene->objects)
		hittable_list_destroy((t_hittable_list *)scene->objects);
	free(scene);
}

t_scene	*scene_create(void)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
	ft_bzero(scene, sizeof(t_scene));
	scene->res.primitives = ptrarr_create();
	scene->res.materials = ptrarr_create();
	scene->res.textures = ptrarr_create();
	scene->world = hittable_list_create();
	scene->objects = hittable_list_create();
	if (!is_all_allocated(scene))
	{
		scene_destroy(scene);
		return (NULL);
	}
	return (scene);
}
