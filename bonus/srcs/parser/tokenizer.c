#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "ptrarr.h"
#include "msgdef.h"
#include "parser_internal.h"

static int	tokenize_comma(t_ptrarr *arr)
{
	char	*comma;

	comma = malloc(sizeof(char) * 2);
	if (!comma)
		return (CODE_ERROR_MALLOC);
	comma[0] = PARSER_COMMA;
	comma[1] = '\0';
	if (ptrarr_append(arr, comma))
	{
		free(comma);
		return (CODE_ERROR_MALLOC);
	}
	return (CODE_OK);
}

static int	tokenize_word(const char *line, t_ptrarr *arr)
{
	int		wordlen;
	char	*word;

	wordlen = 0;
	while (line[wordlen] && !ft_strchr(PARSER_DELIMETER, line[wordlen])
		&& line[wordlen] != PARSER_COMMA)
		wordlen++;
	word = malloc(sizeof(char) * (wordlen + 1));
	if (!word)
		return (CODE_ERROR_MALLOC);
	ft_strlcpy(word, line, wordlen + 1);
	if (ptrarr_append(arr, word))
	{
		free(word);
		return (CODE_ERROR_MALLOC);
	}
	return (CODE_OK);
}

static int	fill_tokens(const char *line, t_ptrarr *arr)
{
	while (*line)
	{
		while (*line && ft_strchr(PARSER_DELIMETER, *line))
			line++;
		if (*line == PARSER_COMMA)
		{
			if (tokenize_comma(arr))
				return (CODE_ERROR_MALLOC);
			line++;
		}
		else
		{
			if (tokenize_word(line, arr))
				return (CODE_ERROR_MALLOC);
			while (*line
				&& !ft_strchr(PARSER_DELIMETER, *line) && *line != PARSER_COMMA)
				line++;
		}
	}
	return (CODE_OK);
}

t_ptrarr	*tokenize(const char *line)
{
	t_ptrarr	*arr;

	arr = ptrarr_create();
	if (!arr)
	{
		printf("%s: "MSG_MALLOC"\n", EXEC_NAME);
		return (NULL);
	}
	if (fill_tokens(line, arr))
	{
		ptrarr_destroy(arr, destroy_pchar);
		printf("%s: "MSG_MALLOC"\n", EXEC_NAME);
		return (NULL);
	}
	return (arr);
}
