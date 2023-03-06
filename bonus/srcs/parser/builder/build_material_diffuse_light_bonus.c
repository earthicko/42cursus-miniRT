#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "print_bonus.h"
#include "builder_internal_bonus.h"

/*
		mt_diffuse_light <name> r , g , b  intensity
		0                1      2 3 4 5 6  7
	∗ identifier: mt_diffuse_light
	∗ name: arbitary given name of the texture
	∗ R,G,B colors in range [0-255]: 0,0,225
	∗ intensity: multiplier to the color
*/
t_bool	is_material_diffuse_light(const t_ptrarr *tokens)
{
	static const int	patternlen = 8;
	static const int	pattern[8] = {
		TOKENTYPE_IDENTIFIER,
		TOKENTYPE_WORD,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER
	};

	if (is_in_pattern(IDENTIFIER_MATERIAL_DIFFUSE_LIGHT,
			pattern, patternlen, tokens))
		return (TRUE);
	return (FALSE);
}

static int	add_material_diffuse_light(t_scene *scene,
				const char *name, t_color color)
{
	t_material	*light;

	if (add_texture_solid(scene, "", color))
		return (CODE_ERROR_MALLOC);
	light = material_diffuse_light_create(name,
			ptrarr_getlast(scene->res.textures));
	if (!light)
		return (CODE_ERROR_MALLOC);
	if (ptrarr_append(scene->res.materials, light))
	{
		light->destroy(light);
		return (CODE_ERROR_MALLOC);
	}
	return (CODE_OK);
}

int	build_material_diffuse_light(const t_ptrarr *tokens, t_scene *scene)
{
	t_color	color;
	double	intensity;

	build_vector(&color, &tokens->data[2]);
	intensity = ft_atof(tokens->data[7]);
	if (is_invalid_color(&color) || is_invalid_length(intensity))
		return (CODE_ERROR_DATA);
	map_color(&color);
	vec3_mult_num_inplace(&color, intensity);
	if (add_material_diffuse_light(scene, tokens->data[1], color))
		return (CODE_ERROR_MALLOC);
	printf("%s: diffuse light material (%s, color ", __func__,
		((t_material *)ptrarr_getlast(scene->res.materials))->name);
	print_vec3(&color);
	printf(")\n");
	return (CODE_OK);
}
