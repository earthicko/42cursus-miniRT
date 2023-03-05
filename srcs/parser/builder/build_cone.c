#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "print.h"
#include "builder_internal.h"

t_bool	is_cone_with_color(const t_ptrarr *tokens);
t_bool	is_cone_with_material(const t_ptrarr *tokens);

static int	add_cone(t_scene *scene, t_cone_info *info, t_material *m)
{
	t_hittable		*cone;

	cone = hittable_cone_create(info, m);
	if (!cone)
		return (CODE_ERROR_MALLOC);
	if (ptrarr_append(scene->res.primitives, cone))
	{
		cone->destroy(cone);
		return (CODE_ERROR_MALLOC);
	}
	if (hittable_list_append(scene->world, cone)
		|| hittable_list_append(scene->objects, cone))
		return (CODE_ERROR_MALLOC);
	return (CODE_OK);
}

int	build_cone_with_color(const t_ptrarr *tokens, t_scene *scene)
{
	t_cone_info	info;
	t_color		color;

	build_vector(&info.center_of_disk, &tokens->data[1]);
	build_vector(&info.axis, &tokens->data[6]);
	info.radius = ft_atof(tokens->data[11]) / 2;
	info.height = ft_atof(tokens->data[12]);
	build_vector(&color, &tokens->data[13]);
	if (is_invalid_normalized_vec3(&info.axis) || is_invalid_color(&color))
		return (CODE_ERROR_DATA);
	vec3_unitize(&info.axis);
	map_color(&color);
	if (add_texture_solid(scene, "", color))
		return (CODE_ERROR_MALLOC);
	if (add_material_lambertian(scene, "", ptrarr_getlast(scene->res.textures)))
		return (CODE_ERROR_MALLOC);
	if (add_cone(scene, &info, ptrarr_getlast(scene->res.materials)))
		return (CODE_ERROR_MALLOC);
	printf("%s: ", __func__);
	print_cone_info(&info);
	printf(", color ");
	print_vec3(&color);
	printf(")\n");
	return (CODE_OK);
}

int	build_cone_with_material(const t_ptrarr *tokens, t_scene *scene)
{
	t_cone_info	info;
	t_material	*mt;

	build_vector(&info.center_of_disk, &tokens->data[1]);
	build_vector(&info.axis, &tokens->data[6]);
	info.radius = ft_atof(tokens->data[11]) / 2;
	info.height = ft_atof(tokens->data[12]);
	mt = scene_search_material(scene, tokens->data[13]);
	if (is_invalid_normalized_vec3(&info.axis) || !mt)
		return (CODE_ERROR_DATA);
	vec3_unitize(&info.axis);
	if (add_cone(scene, &info, mt))
		return (CODE_ERROR_MALLOC);
	printf("%s: ", __func__);
	print_cone_info(&info);
	printf(", material %s)\n", mt->name);
	return (CODE_OK);
}

int	build_cone(const t_ptrarr *tokens, t_scene *scene)
{
	if (is_cone_with_color(tokens))
		return (build_cone_with_color(tokens, scene));
	if (is_cone_with_material(tokens))
		return (build_cone_with_material(tokens, scene));
	return (CODE_ERROR_GENERIC);
}
