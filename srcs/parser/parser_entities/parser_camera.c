#include <stdio.h>
#include "../parser_internal.h"

/*
		C -50.0,0,20 0,0,1 70
	∗ identifier: C
	∗ x,y,z coordinates of the view point: -50.0,0,20
	∗ 3d normalized orientation vector.
		In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
	∗ FOV : Horizontal field of view in degrees in range [0,180]: 70
*/
t_bool	is_camera(const t_ptrarr *tokens)
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
		TOKENTYPE_COMMA,
		TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA,
		TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER
	};

	if (is_in_pattern(IDENTIFIER_CAMERA, pattern, patternlen, tokens))
		return (TRUE);
	return (FALSE);
}

int	build_camera(const t_ptrarr *tokens, t_scene *scene)
{
	(void)tokens;
	(void)scene;
	printf("Unimplemented stub of %s\n", __func__);
	return (CODE_OK);
}
