#include <stdlib.h>
#include <stdio.h>
#include "print.h"
#include "builder_internal.h"

/*
		pl x , y , z   u , v , w   r  ,  g  ,  b
		0  1 2 3 4 5   6 7 8 9 10  11 12 13 14 15
	∗ identifier: pl
	∗ x,y,z coordinates of a point in the plane
	∗ 3d normalized normal vector.
		In range [-1,1] for each x,y,z axis
	∗ R,G,B colors in range [0-255]
*/
t_bool	is_plane_with_color(const t_ptrarr *tokens)
{
	static const int	patternlen = 16;
	static const int	pattern[16] = {
		TOKENTYPE_IDENTIFIER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER
	};

	if (is_in_pattern(IDENTIFIER_PLANE, pattern, patternlen, tokens))
		return (TRUE);
	return (FALSE);
}

/*
		pl x , y , z   u , v , w   material_name
		0  1 2 3 4 5   6 7 8 9 10  11
	∗ identifier: pl
	∗ x,y,z coordinates of a point in the plane
	∗ 3d normalized normal vector.
		In range [-1,1] for each x,y,z axis
	∗ name of material
*/
t_bool	is_plane_with_material(const t_ptrarr *tokens)
{
	static const int	patternlen = 12;
	static const int	pattern[12] = {
		TOKENTYPE_IDENTIFIER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_WORD
	};

	if (is_in_pattern(IDENTIFIER_PLANE, pattern, patternlen, tokens))
		return (TRUE);
	return (FALSE);
}

t_bool	is_plane(const t_ptrarr *tokens)
{
	if (is_plane_with_color(tokens) || is_plane_with_material(tokens))
		return (TRUE);
	return (FALSE);
}
