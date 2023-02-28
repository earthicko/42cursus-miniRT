#include "parser_internal.h"

/*
	returns TRUE if line matches pattern, FALSE if doesn't,
	negative if error occurs.
*/
int	parse_line(const char *line, t_scene *scene,
	t_patternmatcher tester, t_builder builder)
{
	t_ptrarr	*tokens;
	int			stat;

	tokens = tokenize(line);
	if (!tokens)
		return (CODE_ERROR_MALLOC);
	stat = FALSE;
	if (tester(tokens))
	{
		stat = builder(tokens, scene);
		if (!stat)
			stat = TRUE;
	}
	ptrarr_destroy(tokens, TRUE);
	return (stat);
}
