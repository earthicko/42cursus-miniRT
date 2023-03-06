#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "print_bonus.h"
#include "builder_internal_bonus.h"

/*
		mt_metal <name> <texture_name> <fuzz>
		0        1      2              3
	∗ identifier: mt_metal
	∗ name: arbitary given name of the material
	∗ texture_name: name of a texture that will be used as albedo
	∗ fuzz: fuzziness value (0, 1)
*/
t_bool	is_material_metal(const t_ptrarr *tokens)
{
	static const int	patternlen = 4;
	static const int	pattern[4] = {
		TOKENTYPE_IDENTIFIER,
		TOKENTYPE_WORD,
		TOKENTYPE_WORD,
		TOKENTYPE_NUMBER
	};

	if (is_in_pattern(IDENTIFIER_MATERIAL_METAL,
			pattern, patternlen, tokens))
		return (TRUE);
	return (FALSE);
}

static int	add_material_metal(t_scene *scene,
				const char *name, t_texture *texture, double fuzz)
{
	t_material	*metal;

	metal = material_metal_create(name, texture, fuzz);
	if (!metal)
		return (CODE_ERROR_MALLOC);
	if (ptrarr_append(scene->res.materials, metal))
	{
		metal->destroy(metal);
		return (CODE_ERROR_MALLOC);
	}
	return (CODE_OK);
}

int	build_material_metal(const t_ptrarr *tokens, t_scene *scene)
{
	const char			*name = tokens->data[1];
	const char			*tx_name = tokens->data[2];
	t_texture			*tx;
	const double		fuzz = ft_atof(tokens->data[3]);
	t_material_metal	*metal;

	tx = scene_search_texture(scene, tx_name);
	if (!tx || is_invalid_ratio(fuzz))
		return (CODE_ERROR_GENERIC);
	if (add_material_metal(scene, name, tx, fuzz))
		return (CODE_ERROR_MALLOC);
	metal = (t_material_metal *)ptrarr_getlast(scene->res.materials);
	printf("%s: metal material (%s, texture %s, fuzz %.2f)\n", __func__,
		metal->name, metal->albedo->name, metal->fuzz);
	return (CODE_OK);
}
