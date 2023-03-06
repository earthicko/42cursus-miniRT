#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "print_bonus.h"
#include "builder_internal_bonus.h"

/*
		bo x , y , z   u , v , w    W   H   D    r  ,  g  ,  b
		0  1 2 3 4 5   6 7 8 9 10   11  12  13   14 15 16 17 18
	∗ identifier: bo
	∗ x,y,z coordinates of the center of the box
	∗ x,y,z rotation angles of each axis
	∗ the box width
	∗ the box height
	∗ the box depth
	∗ R,G,B colors in range [0,255]
*/
t_bool	is_box_with_color(const t_ptrarr *tokens)
{
	static const int	patternlen = 19;
	static const int	pattern[19] = {
		TOKENTYPE_IDENTIFIER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER, TOKENTYPE_NUMBER, TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
	};

	if (is_in_pattern(IDENTIFIER_BOX, pattern, patternlen, tokens))
		return (TRUE);
	return (FALSE);
}

/*
		bo x , y , z   u , v , w    W   H   D    mt1 mt2 mt3 mt4 mt5 mt6
		0  1 2 3 4 5   6 7 8 9 10   11  12  13   14  15  16  17  18  19
	∗ identifier: bo
	∗ x,y,z coordinates of the center of the box
	∗ x,y,z rotation angles of each axis
	∗ the box width
	∗ the box height
	∗ the box depth
	∗ material name of each faces (1 ~ 6)
*/
t_bool	is_box_with_material(const t_ptrarr *tokens)
{
	static const int	patternlen = 20;
	static const int	pattern[20] = {
		TOKENTYPE_IDENTIFIER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER, TOKENTYPE_NUMBER, TOKENTYPE_NUMBER,
		TOKENTYPE_WORD,
		TOKENTYPE_WORD,
		TOKENTYPE_WORD,
		TOKENTYPE_WORD,
		TOKENTYPE_WORD,
		TOKENTYPE_WORD,
	};

	if (is_in_pattern(IDENTIFIER_BOX, pattern, patternlen, tokens))
		return (TRUE);
	return (FALSE);
}

t_bool	is_box(const t_ptrarr *tokens)
{
	if (is_box_with_color(tokens) || is_box_with_material(tokens))
		return (TRUE);
	return (FALSE);
}
