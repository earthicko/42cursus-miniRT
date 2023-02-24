#include <stdio.h>
#include "../parser_internal.h"

/*
		sp 0.0,0.0,20.6 12.6 10,0,255
	∗ identifier: sp
	∗ x,y,z coordinates of the sphere center: 0.0,0.0,20.6
	∗ the sphere diameter: 12.6
	∗ R,G,B colors in range [0-255]: 10, 0, 255
*/
t_bool	is_sphere(const t_ptrarr *tokens)
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
		TOKENTYPE_NUMBER
	};

	if (is_in_pattern(IDENTIFIER_SPHERE, pattern, patternlen, tokens))
		return (TRUE);
	return (FALSE);
}

int	build_sphere(const t_ptrarr *tokens, t_scene *scene)
{
	(void)tokens;
	(void)scene;
	printf("Unimplemented stub of %s\n", __func__);
	return (CODE_OK);
}
