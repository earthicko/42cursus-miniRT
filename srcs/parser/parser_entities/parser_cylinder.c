#include <stdio.h>
#include "../parser_internal.h"

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

int	build_cylinder(const t_ptrarr *tokens, t_scene *scene)
{
	(void)tokens;
	(void)scene;
	printf("Unimplemented stub of %s\n", __func__);
	return (CODE_OK);
}
