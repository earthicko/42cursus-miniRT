#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "number.h"
#include "print.h"
#include "builder_internal.h"

/*
		sp x , y , z   D   r  ,  g  ,  b
		0  1 2 3 4 5   6   7  8  9  10 11
	∗ identifier: sp
	∗ x,y,z coordinates of the sphere center
	∗ the sphere diameter
	∗ R,G,B colors in range [0-255]
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
