#include <stdio.h>
#include "libft.h"
#include "ptrarr.h"
#include "msgdef.h"
#include "../parser_internal.h"

t_bool	is_plane(t_ptrarr *tokens)
{
	const static int	patternlen = 16;
	const static int	pattern[16] = {
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

int	build_plane(char *line)
{
	(void)line;
	printf("Unimplemented stub of %s\n", __func__);
	return (CODE_OK);
}
