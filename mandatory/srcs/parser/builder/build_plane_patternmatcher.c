#include <stdlib.h>
#include <stdio.h>
#include "print.h"
#include "builder_internal.h"

/*
		pl x , y , z   u , v , w   scale  r  ,  g  ,  b
		0  1 2 3 4 5   6 7 8 9 10  11     12 13 14 15 16
	∗ identifier: pl
	∗ x,y,z coordinates of a point in the plane
	∗ 3d normalized normal vector.
		In range [-1,1] for each x,y,z axis
	∗ scale value to be used in texture mapping
	∗ R,G,B colors in range [0-255]
*/
t_bool	is_plane(const t_ptrarr *tokens)
{
	static const int	patternlen = 17;
	static const int	pattern[17] = {
		TOKENTYPE_IDENTIFIER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER
	};

	if (is_in_pattern(IDENTIFIER_PLANE, pattern, patternlen, tokens))
		return (TRUE);
	return (FALSE);
}
