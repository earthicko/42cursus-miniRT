#include <stdlib.h>
#include <stdio.h>
#include "print.h"
#include "builder_internal.h"

/*
		tx_solid <name> 50, 100, 150
		0        1      2 3 4  5 6
	∗ identifier: tx solid
	∗ name: aarbitary given name of the texture
	∗ R,G,B colors in range [0-255]: 0,0,225
*/
t_bool	is_texture_solid(const t_ptrarr *tokens)
{
	static const int	patternlen = 7;
	static const int	pattern[7] = {
		TOKENTYPE_IDENTIFIER,
		TOKENTYPE_WORD,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER
	};

	if (is_in_pattern(IDENTIFIER_TEXTURE_SOLID, pattern, patternlen, tokens))
		return (TRUE);
	return (FALSE);
}

int	build_texture_solid(const t_ptrarr *tokens, t_scene *scene)
{
	t_color	color;

	build_vector(&color, &tokens->data[2]);
	if (is_invalid_color(&color))
		return (CODE_ERROR_DATA);
	map_color(&color);
	if (add_texture_solid(scene, tokens->data[1], color))
		return (CODE_ERROR_MALLOC);
	printf("%s: solid texture (%s, color ", __func__,
		((t_texture *)ptrarr_getlast(scene->res.textures))->name);
	print_vec3(&color);
	printf(")\n");
	return (CODE_OK);
}
