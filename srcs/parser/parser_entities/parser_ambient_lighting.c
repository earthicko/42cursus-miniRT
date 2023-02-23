#include <stdio.h>
#include "libft.h"
#include "ptrarr.h"
#include "msgdef.h"
#include "../parser_internal.h"

t_bool	is_ambient_lighting(t_ptrarr *tokens)
{
	const static int	patternlen = 7;
	const static int	pattern[7] = {
		TOKENTYPE_IDENTIFIER,
		TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA,
		TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA,
		TOKENTYPE_NUMBER
	};

	if (is_in_pattern(IDENTIFIER_AMBIENTLIGHTING, pattern, patternlen, tokens))
		return (TRUE);
	return (FALSE);
}

int	build_ambient_lighting(char *line)
{
	(void)line;
	printf("Unimplemented stub of %s\n", __func__);
	return (CODE_OK);
}
