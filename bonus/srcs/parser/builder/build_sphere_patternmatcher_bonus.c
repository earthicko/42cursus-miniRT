#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "number_bonus.h"
#include "print_bonus.h"
#include "builder_internal_bonus.h"

/*
		sp x , y , z   D   r  ,  g  ,  b
		0  1 2 3 4 5   6   7  8  9  10 11
	∗ identifier: sp
	∗ x,y,z coordinates of the sphere center
	∗ the sphere diameter
	∗ R,G,B colors in range [0-255]
*/
t_bool	is_sphere_with_color(const t_ptrarr *tokens)
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

/*
		sp x , y , z   D   material_name
		0  1 2 3 4 5   6   7
	∗ identifier: sp
	∗ x,y,z coordinates of the sphere center
	∗ the sphere diameter
	∗ name of the material
*/
t_bool	is_sphere_with_material(const t_ptrarr *tokens)
{
	static const int	patternlen = 8;
	static const int	pattern[8] = {
		TOKENTYPE_IDENTIFIER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER,
		TOKENTYPE_WORD
	};

	if (is_in_pattern(IDENTIFIER_SPHERE, pattern, patternlen, tokens))
		return (TRUE);
	return (FALSE);
}

t_bool	is_sphere(const t_ptrarr *tokens)
{
	if (is_sphere_with_color(tokens) || is_sphere_with_material(tokens))
		return (TRUE);
	return (FALSE);
}
