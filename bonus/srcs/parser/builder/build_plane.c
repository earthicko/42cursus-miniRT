#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "print.h"
#include "builder_internal.h"

t_bool	is_plane_with_color(const t_ptrarr *tokens);
t_bool	is_plane_with_material(const t_ptrarr *tokens);

static int	add_plane(t_scene *scene, t_ray dir, double scale, t_material *m)
{
	t_hittable	*plane;

	plane = hittable_plane_create(dir.orig, dir.dir, m, scale);
	if (!plane)
		return (CODE_ERROR_MALLOC);
	if (ptrarr_append(scene->res.primitives, plane))
	{
		plane->destroy(plane);
		return (CODE_ERROR_MALLOC);
	}
	if (hittable_list_append(scene->world, plane)
		|| hittable_list_append(scene->objects, plane))
		return (CODE_ERROR_MALLOC);
	return (CODE_OK);
}

static void	print_plane_with_color(
				const char *func, t_ray dir, t_color color, double scale)
{
	printf("%s: plane (point ", func);
	print_vec3(&dir.orig);
	printf(", normal ");
	print_vec3(&dir.dir);
	printf(", scale %.2f, color ", scale);
	print_vec3(&color);
	printf(")\n");
}

int	build_plane_with_color(const t_ptrarr *tokens, t_scene *scene)
{
	t_ray	dir;
	t_color	color;
	double	scale;

	build_vector(&dir.orig, &tokens->data[1]);
	build_vector(&dir.dir, &tokens->data[6]);
	build_vector(&color, &tokens->data[12]);
	scale = ft_atof(tokens->data[11]);
	if (is_invalid_normalized_vec3(&dir.dir) || is_invalid_color(&color)
		|| is_invalid_length(scale))
		return (CODE_ERROR_DATA);
	vec3_unitize(&dir.dir);
	map_color(&color);
	if (add_texture_solid(scene, "", color))
		return (CODE_ERROR_MALLOC);
	if (add_material_lambertian(scene, "", ptrarr_getlast(scene->res.textures)))
		return (CODE_ERROR_MALLOC);
	if (add_plane(scene, dir, scale, ptrarr_getlast(scene->res.materials)))
		return (CODE_ERROR_MALLOC);
	print_plane_with_color(__func__, dir, color, scale);
	return (CODE_OK);
}

int	build_plane_with_material(const t_ptrarr *tokens, t_scene *scene)
{
	t_ray		dir;
	t_material	*mt;
	double		scale;

	build_vector(&dir.orig, &tokens->data[1]);
	build_vector(&dir.dir, &tokens->data[6]);
	scale = ft_atof(tokens->data[11]);
	mt = scene_search_material(scene, tokens->data[12]);
	if (is_invalid_normalized_vec3(&dir.dir) || is_invalid_length(scale) || !mt)
		return (CODE_ERROR_DATA);
	vec3_unitize(&dir.dir);
	if (add_plane(scene, dir, scale, mt))
		return (CODE_ERROR_MALLOC);
	printf("%s: plane (point ", __func__);
	print_vec3(&dir.orig);
	printf(", normal ");
	print_vec3(&dir.dir);
	printf(", scale %.2f, material %s)\n", scale, mt->name);
	return (CODE_OK);
}

int	build_plane(const t_ptrarr *tokens, t_scene *scene)
{
	if (is_plane_with_color(tokens))
		return (build_plane_with_color(tokens, scene));
	if (is_plane_with_material(tokens))
		return (build_plane_with_material(tokens, scene));
	return (CODE_ERROR_DATA);
}
