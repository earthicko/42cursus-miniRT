#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "print.h"
#include "builder_internal.h"

/*
		L -40.0,50.0,0.0 0.6 10,0,255
	∗ identifier: L
	∗ x,y,z coordinates of the light point: -40.0,50.0,0.0
	∗ the light brightness ratio in range [0.0,1.0]: 0.6
	∗ (unused in mandatory part)R,G,B colors in range [0-255]: 10, 0, 255
*/
t_bool	is_light(const t_ptrarr *tokens)
{
	static const int	patternlen = 12;
	static const int	pattern[12] = {
		TOKENTYPE_IDENTIFIER,
		TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA,
		TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA,
		TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA,
		TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA,
		TOKENTYPE_NUMBER,
	};

	if (is_in_pattern(IDENTIFIER_LIGHT, pattern, patternlen, tokens))
		return (TRUE);
	return (FALSE);
}

static int	add_material_diffuse_light(t_scene *scene, t_color color)
{
	t_material	*light;

	vec3_mult_num_inplace(&color, LIGHT_DEFAULT_INTENSITY);
	if (add_texture_solid(scene, color))
		return (CODE_ERROR_MALLOC);
	light = material_diffuse_light_create(ptrarr_getlast(scene->res.textures));
	if (!light)
		return (CODE_ERROR_MALLOC);
	if (ptrarr_append(scene->res.materials, light))
	{
		free(light);
		return (CODE_ERROR_MALLOC);
	}
	return (CODE_OK);
}

static int	add_light(t_scene *scene, t_point coord, t_material *m)
{
	t_hittable	*light;

	light = hittable_sphere_create(coord, LIGHT_DEFAULT_RADIUS, m);
	if (!light)
		return (CODE_ERROR_MALLOC);
	if (ptrarr_append(scene->res.primitives, light))
	{
		free(light);
		return (CODE_ERROR_MALLOC);
	}
	if (hittable_list_append(scene->world, light))
		return (CODE_ERROR_MALLOC);
	return (CODE_OK);
}

int	build_light(const t_ptrarr *tokens, t_scene *scene)
{
	t_point	coord;
	double	ratio;
	t_color	color;

	build_vector(&coord, &tokens->data[1]);
	ratio = ft_atof(tokens->data[6]);
	build_vector(&color, &tokens->data[7]);
	if (is_invalid_ratio(ratio) || is_invalid_color(&color))
		return (CODE_ERROR_DATA);
	map_color(&color);
	vec3_mult_num_inplace(&color, ratio);
	if (add_material_diffuse_light(scene, color))
		return (CODE_ERROR_MALLOC);
	if (add_light(scene, coord, ptrarr_getlast(scene->res.materials)))
		return (CODE_ERROR_MALLOC);
	printf("%s: light (coord ", __func__);
	print_vec3(&coord);
	printf(", ratio %.2f, color ", ratio);
	print_vec3(&color);
	printf(")\n");
	return (CODE_OK);
}
