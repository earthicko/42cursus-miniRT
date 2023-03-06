#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "ptrarr.h"
#include "libft.h"
#include "msgdef.h"
#include "texture.h"

static t_bool	load_file_init(
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

static void	destroy_pchar(void *pchar)
{
	free((char *)pchar);
}

t_ptrarr	*load_file(const char *path)
{
	t_ptrarr	*arr;
	int			fd;
	char		*newline;

	if (!load_file_init(path, &arr, &fd))
		return (NULL);
	while (TRUE)
	{
		newline = get_next_line(fd);
		if (!newline)
			return (arr);
		if (is_samestr(newline, "\n") || ft_strncmp(newline, "/*", 2) == 0)
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
