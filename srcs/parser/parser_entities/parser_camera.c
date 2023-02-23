#include <stdio.h>
#include "libft.h"
#include "ptrarr.h"
#include "msgdef.h"
#include "../parser_internal.h"

t_bool	is_camera(t_ptrarr *tokens)
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

int	build_camera(char *line)
{
	(void)line;
	printf("Unimplemented stub of %s\n", __func__);
	return (CODE_OK);
}
