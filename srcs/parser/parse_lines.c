#include <stdio.h>
#include "libft.h"
#include "ptrarr.h"
#include "msgdef.h"
#include "parser_internal.h"

int		parse_unique_entity_loop(
			t_bool *already_found, const char *line, t_scene *scene);
int		parse_common_entity(const char *line, t_scene *scene);
t_bool	all_unique_entities_found(t_bool *map);

void	parse_setting_loop(const char *line, t_scene *scene)
{
	int		i;

	i = 0;
	while (i < N_IDENTIFIER_SETTING)
	{
		parse_line(line, scene,
			setting_patternmatcher_manager(i), setting_builder_manager(i));
		i++;
	}
}

// TODO: utilize parse_setting_loop()
int	parse_lines(const t_ptrarr *lines, t_scene *scene)
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
		{
			printf("%s: "MSG_PARSEFAIL"\n", EXEC_NAME, lines->data[i]);
			return (stat);
		}
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
