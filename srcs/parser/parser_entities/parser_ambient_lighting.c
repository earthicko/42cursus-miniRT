#include <stdio.h>
#include "../parser_internal.h"

t_bool	is_ambient_lighting(const t_ptrarr *tokens)
{
	static const int	patternlen = 7;
	static const int	pattern[7] = {
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

int	build_ambient_lighting(const t_ptrarr *tokens)
{
	(void)tokens;
	printf("Unimplemented stub of %s\n", __func__);
	return (CODE_OK);
}
