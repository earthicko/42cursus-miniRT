#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "print.h"
#include "builder_internal.h"

/*
		co 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
	∗ identifier: co
	∗ x,y,z coordinates of the center of the cone: 50.0,0.0,20.6
	∗ 3d normalized vector of axis of cone.
		In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
	∗ the cone diameter: 14.2
	∗ the cone height: 21.42
	∗ R,G,B colors in range [0,255]: 10, 0, 255
*/
t_bool	is_cone(const t_ptrarr *tokens)
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

	if (is_in_pattern(IDENTIFIER_CONE, pattern, patternlen, tokens))
		return (TRUE);
	return (FALSE);
}

static int	add_cone(t_scene *scene, t_cone_info *info, t_material *m)
{
	t_hittable		*cone;

	cone = hittable_cone_create(info, m);
	if (!cone)
		return (CODE_ERROR_MALLOC);
	if (ptrarr_append(scene->res.primitives, cone))
	{
		free(cone);
		return (CODE_ERROR_MALLOC);
	}
	if (hittable_list_append(scene->world, cone)
		|| hittable_list_append(scene->objects, cone))
		return (CODE_ERROR_MALLOC);
	return (CODE_OK);
}

int	build_cone(const t_ptrarr *tokens, t_scene *scene)
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
