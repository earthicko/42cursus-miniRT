#include <stdlib.h>
#include <stdio.h>
#include "print.h"
#include "builder_internal.h"

/*
		mt_lambertian <name> <texture_name>
		0             1      2
	∗ identifier: mt_lambertian
	∗ name: arbitary given name of the material
	∗ texture_name: name of a texture that will be used as albedo
*/
t_bool	is_material_lambertian(const t_ptrarr *tokens)
{
	static const int	patternlen = 3;
	static const int	pattern[3] = {
		TOKENTYPE_IDENTIFIER,
		TOKENTYPE_WORD,
		TOKENTYPE_WORD
	};

	if (is_in_pattern(IDENTIFIER_MATERIAL_LAMBERTIAN,
			pattern, patternlen, tokens))
		return (TRUE);
	return (FALSE);
}

int	build_material_lambertian(const t_ptrarr *tokens, t_scene *scene)
{
	const char				*name = tokens->data[1];
	const char				*tx_name = tokens->data[2];
	t_texture				*tx;
	t_material_lambertian	*lambertian;

	tx = scene_search_texture(scene, tx_name);
	if (!tx)
		return (CODE_ERROR_MALLOC);
	if (add_material_lambertian(scene, name, tx))
		return (CODE_ERROR_MALLOC);
	lambertian = (t_material_lambertian *)ptrarr_getlast(scene->res.materials);
	printf("%s: lambertian material (%s, texture %s)\n", __func__,
		lambertian->name, lambertian->albedo->name);
	return (CODE_OK);
}
