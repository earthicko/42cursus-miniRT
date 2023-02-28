#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "print.h"
#include "builder_internal.h"

/*
		tx solid <name> 50, 100, 150
	∗ identifier: tx solid
	∗ name: aarbitary given name of the texture
	∗ R,G,B colors in range [0-255]: 0,0,225
*/
t_bool	is_texture_solid(const t_ptrarr *tokens)
{
	static const int	patternlen = 8;
	static const int	pattern[8] = {
		TOKENTYPE_IDENTIFIER,
		TOKENTYPE_WORD, TOKENTYPE_WORD,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER
	};

	if (is_in_pattern(IDENTIFIER_TEXTURE, pattern, patternlen, tokens)
		&& is_samestr((char *)(tokens->data[1]), "solid"))
		return (TRUE);
	return (FALSE);
}

int	build_texture_solid(const t_ptrarr *tokens, t_scene *scene)
{
	t_color	color;

	build_vector(&color, &tokens->data[3]);
	if (is_invalid_color(&color))
		return (CODE_ERROR_DATA);
	map_color(&color);
	if (add_texture_solid(scene, tokens->data[2], color))
		return (CODE_ERROR_MALLOC);
	printf("%s: solid texture (%s, color ", __func__,
		((t_texture *)ptrarr_getlast(scene->res.textures))->name);
	print_vec3(&color);
	printf(")\n");
	return (CODE_OK);
}
