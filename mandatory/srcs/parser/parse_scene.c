#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft.h"
#include "ptrarr.h"
#include "msgdef.h"
#include "print.h"
#include "parser_internal.h"

static t_bool	read_file_to_strarr_init(
		const char *path, t_ptrarr **arr, int *fd)
{
	*arr = ptrarr_create();
	if (!(*arr))
	{
		printf("%s: "MSG_MALLOC"\n", EXEC_NAME);
		return (FALSE);
	}
	*fd = open(path, O_RDONLY);
	if (*fd < 0)
	{
		ptrarr_destroy(*arr, NULL);
		perror(EXEC_NAME);
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
	printf("%s: parsing complete. results:\n", __func__);
	printf("\t%d primitives, %d materials, %d textures\n",
		scene->res.primitives->len,
		scene->res.materials->len,
		scene->res.textures->len);
	printf("\t%d objects, %d lights\n",
		((t_hittable_list *)scene->objects)->elements->len,
		((t_hittable_list *)scene->world)->elements->len
		- ((t_hittable_list *)scene->objects)->elements->len);
	printf("\n");
	return (stat);
}
