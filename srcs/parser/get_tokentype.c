#include <stdio.h>
#include <math.h>
#include "libft.h"
#include "ptrarr.h"
#include "parser_internal.h"

t_bool	is_identifier(const char *word)
{
	int	i;

	i = 0;
	while (i < N_IDENTIFIER)
	{
		if (ft_strncmp(tokenname_manager(i), word,
				ft_strlen(tokenname_manager(i)) + 1) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	is_number(const char *word)
{
	double	num;

	if (ft_atof_if_valid(word, &num))
		return (FALSE);
	return (TRUE);
}

t_bool	is_comma(const char *word)
{
	if (ft_strncmp(PARSER_COMMA_STR, word,
			ft_strlen(PARSER_COMMA_STR) + 1) == 0)
		return (TRUE);
	return (FALSE);
}

t_bool	is_word(const char *word)
{
	(void)word;
	return (TRUE);
}

t_bool	is_in_pattern(const char *identifier,
	const int *pattern, const int patternlen, const t_ptrarr *tokens)
{
	int	i;

	i = 0;
	while (i < patternlen)
	{
		if (i >= tokens->len)
			return (FALSE);
		if (pattern[i] == TOKENTYPE_IDENTIFIER
			&& ft_strncmp(tokens->data[i], identifier,
				ft_strlen(identifier) + 1))
			return (FALSE);
		if (!wordtester_manager(pattern[i])(tokens->data[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
