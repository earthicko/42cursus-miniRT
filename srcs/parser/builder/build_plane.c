#include <stdlib.h>
#include <stdio.h>
#include "print.h"
#include "builder_internal.h"

t_bool	is_plane_with_color(const t_ptrarr *tokens);
t_bool	is_plane_with_material(const t_ptrarr *tokens);

static int	add_plane(t_scene *scene, t_point p, t_vec3 norm, t_material *m)
{
	t_hittable	*plane;

	plane = hittable_plane_create(p, norm, m);
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

int	build_plane_with_color(const t_ptrarr *tokens, t_scene *scene)
{
	t_point	p;
	t_vec3	norm;
	t_color	color;

	build_vector(&p, &tokens->data[1]);
	build_vector(&norm, &tokens->data[6]);
	build_vector(&color, &tokens->data[11]);
	if (is_invalid_normalized_vec3(&norm) || is_invalid_color(&color))
		return (CODE_ERROR_DATA);
	map_color(&color);
	if (add_texture_solid(scene, "", color))
		return (CODE_ERROR_MALLOC);
	if (add_material_lambertian(scene, "", ptrarr_getlast(scene->res.textures)))
		return (CODE_ERROR_MALLOC);
	if (add_plane(scene, p, norm, ptrarr_getlast(scene->res.materials)))
		return (CODE_ERROR_MALLOC);
	printf("%s: plane (point ", __func__);
	print_vec3(&p);
	printf(", normal ");
	print_vec3(&norm);
	printf(", color ");
	print_vec3(&color);
	printf(")\n");
	return (CODE_OK);
}

int	build_plane_with_material(const t_ptrarr *tokens, t_scene *scene)
{
	t_point		p;
	t_vec3		norm;
	t_material	*mt;

	build_vector(&p, &tokens->data[1]);
	build_vector(&norm, &tokens->data[6]);
	mt = scene_search_material(scene, tokens->data[11]);
	if (is_invalid_normalized_vec3(&norm) || !mt)
		return (CODE_ERROR_DATA);
	if (add_plane(scene, p, norm, mt))
		return (CODE_ERROR_MALLOC);
	printf("%s: plane (point ", __func__);
	print_vec3(&p);
	printf(", normal ");
	print_vec3(&norm);
	printf(", material %s)\n", mt->name);
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
