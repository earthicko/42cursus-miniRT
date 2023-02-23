#include <stddef.h>
#include "parser_internal.h"

char	*tokenname_manager(int i)
{
	const static char	*names[N_IDENTIFIER] = {
		IDENTIFIER_AMBIENTLIGHTING,
		IDENTIFIER_CAMERA,
		IDENTIFIER_LIGHT,
		IDENTIFIER_SPHERE,
		IDENTIFIER_PLANE,
		IDENTIFIER_CYLINDER
	};

	if (i < 0 || i >= N_IDENTIFIER)
		return (NULL);
	return ((char *)names[i]);
}

t_wordtester	wordtester_manager(int i)
{
	const static t_wordtester	testers[3] = {
		is_identifier,
		is_number,
		is_comma
	};

	if (i < 0 || i >= N_TOKENTYPE)
		return (NULL);
	return (testers[i]);
}
