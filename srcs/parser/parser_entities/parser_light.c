#include <stdio.h>
#include "../parser_internal.h"

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

int	build_light(const t_ptrarr *tokens, t_scene *scene)
{
	(void)tokens;
	(void)scene;
	printf("Unimplemented stub of %s\n", __func__);
	return (CODE_OK);
}
