#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "print.h"
#include "builder_internal.h"

/*
		cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
	∗ identifier: cy
	∗ x,y,z coordinates of the center of the cylinder: 50.0,0.0,20.6
	∗ 3d normalized vector of axis of cylinder.
		In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
	∗ the cylinder diameter: 14.2
	∗ the cylinder height: 21.42
	∗ R,G,B colors in range [0,255]: 10, 0, 255
*/
t_bool	is_cylinder(const t_ptrarr *tokens)
{
	static const int	patternlen = 18;
	static const int	pattern[18] = {
		TOKENTYPE_IDENTIFIER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
	};

	if (is_in_pattern(IDENTIFIER_CYLINDER, pattern, patternlen, tokens))
		return (TRUE);
	return (FALSE);
}

static int	add_cylinder(t_scene *scene, t_cylinder_info *info, t_material *m)
{
	t_hittable		*cylinder;

	cylinder = hittable_cylinder_create(info, m);
	if (!cylinder)
		return (CODE_ERROR_MALLOC);
	if (ptrarr_append(scene->res.primitives, cylinder))
	{
		free(cylinder);
		return (CODE_ERROR_MALLOC);
	}
	if (hittable_list_append(scene->world, cylinder)
		|| hittable_list_append(scene->objects, cylinder))
		return (CODE_ERROR_MALLOC);
	return (CODE_OK);
}

int	build_cylinder(const t_ptrarr *tokens, t_scene *scene)
{
	t_cylinder_info	info;
	t_color			color;

	build_vector(&info.center_of_cylinder, &tokens->data[1]);
	build_vector(&info.axis, &tokens->data[6]);
	info.radius = ft_atof(tokens->data[11]) / 2;
	info.height = ft_atof(tokens->data[12]);
	build_vector(&color, &tokens->data[13]);
	if (is_invalid_normalized_vec3(&info.axis) || is_invalid_color(&color))
		return (CODE_ERROR_DATA);
	map_color(&color);
	if (add_texture_solid(scene, "", color))
		return (CODE_ERROR_MALLOC);
	if (add_material_lambertian(scene, ptrarr_getlast(scene->res.textures)))
		return (CODE_ERROR_MALLOC);
	if (add_cylinder(scene, &info, ptrarr_getlast(scene->res.materials)))
		return (CODE_ERROR_MALLOC);
	printf("%s: ", __func__);
	print_cylinder_info(&info);
	printf(", color ");
	print_vec3(&color);
	printf(")\n");
	return (CODE_OK);
}
