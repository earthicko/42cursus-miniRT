#include "libft.h"
#include "ptrarr.h"
#include "msgdef.h"
#include "../parser_internal.h"

/*
	returns TRUE if line matches one of unique entities,
	FALSE if line matches none,
	negative if error occurs.
*/
static int	parse_unique_entity_loop(
			t_bool *already_found, const char *line, t_scene *scene)
{
	int		i;
	int		stat;
	t_bool	found_once;

	found_once = FALSE;
	i = 0;
	while (i < N_IDENTIFIER_UNIQUE)
	{
		stat = parse_line(line, scene,
				unique_patternmatcher_manager(i), unique_builder_manager(i));
		if (stat == TRUE)
		{
			found_once = TRUE;
			if (already_found[i])
			{
				ft_dprintf(2, "%s: "MSG_DUPLICATE"\n", EXEC_NAME);
				return (CODE_ERROR_DATA);
			}
			already_found[i] = TRUE;
		}
		else if (stat < 0)
			return (stat);
		i++;
	}
	return (found_once);
}

/*
	returns TRUE if line matches one of common entities,
	FALSE if line matches none,
	negative if error occurs.
*/
static int	parse_common_entity_loop(const char *line, t_scene *scene)
{
	int		i;
	int		stat;

	i = 0;
	while (i < N_IDENTIFIER_COMMON)
	{
		stat = parse_line(line, scene,
				common_patternmatcher_manager(i), common_builder_manager(i));
		if (stat)
			return (stat);
		i++;
	}
	return (FALSE);
}

static int	parse_common_entity(const char *line, t_scene *scene)
{
	int	stat;

	stat = parse_common_entity_loop(line, scene);
	if (stat < 0)
		return (stat);
	if (stat == FALSE)
	{
		ft_dprintf(2, "%s: "MSG_PARSEFAIL"\n", EXEC_NAME, line);
		return (CODE_ERROR_DATA);
	}
	return (CODE_OK);
}

static t_bool	all_unique_entities_found(t_bool *map)
{
	int	i;

	i = 0;
	while (i < N_IDENTIFIER_UNIQUE)
	{
		if (map[i] == FALSE)
		{
			ft_dprintf(2, "%s: "MSG_ENTITY_NOTFOUND"\n", EXEC_NAME);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	parse_entities(const t_ptrarr *lines, t_scene *scene)
{
	int			i;
	int			stat;
	t_bool		already_found[N_IDENTIFIER_UNIQUE];

	ft_memset(already_found, FALSE, sizeof(already_found));
	i = 0;
	while (i < lines->len)
	{
		stat = parse_unique_entity_loop(already_found, lines->data[i], scene);
		if (stat < 0)
			return (stat);
		if (stat == FALSE)
		{
			stat = parse_common_entity(lines->data[i], scene);
			if (stat < 0)
				return (stat);
		}
		i++;
	}
	if (!all_unique_entities_found(already_found))
		return (CODE_ERROR_DATA);
	return (CODE_OK);
}
