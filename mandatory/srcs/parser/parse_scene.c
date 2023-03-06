#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft.h"
#include "ptrarr.h"
#include "parser_internal.h"

static t_bool	read_file_to_strarr_init(
		const char *path, t_ptrarr **arr, int *fd)
{
	*arr = ptrarr_create();
	if (!(*arr))
		return (FALSE);
	*fd = open(path, O_RDONLY);
	if (*fd < 0)
	{
		ptrarr_destroy(*arr, NULL);
		return (FALSE);
	}
	return (TRUE);
}

void	destroy_pchar(void *pchar)
{
	free((char *)pchar);
}

t_ptrarr	*read_file_to_strarr(const char *path)
{
	t_ptrarr	*arr;
	int			fd;
	char		*newline;

	if (!read_file_to_strarr_init(path, &arr, &fd))
		return (NULL);
	while (TRUE)
	{
		newline = get_next_line(fd);
		if (!newline)
			return (arr);
		if ((ft_strlen(newline) == 1 && newline[0] == '\n')
			|| newline[0] == PARSER_COMMENT)
		{
			free(newline);
			continue ;
		}
		if (newline[ft_strlen(newline) - 1] == '\n')
			newline[ft_strlen(newline) - 1] = '\0';
		if (ptrarr_append(arr, newline))
		{
			ptrarr_destroy(arr, destroy_pchar);
			return (NULL);
		}
	}
}

int	parse_scene(const char *path, t_scene *scene)
{
	int			stat;
	t_ptrarr	*lines;

	lines = read_file_to_strarr(path);
	if (!lines)
		return (CODE_ERROR_IO);
	stat = parse_lines(lines, scene);
	ptrarr_destroy(lines, destroy_pchar);
	if (stat)
		return (stat);
	return (stat);
}
