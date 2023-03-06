/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:48:54 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "ptrarr.h"
#include "parser_internal.h"

int		parse_unique_entity_loop(
			t_bool *already_found, const char *line, t_scene *scene);
int		parse_common_entity(const char *line, t_scene *scene);
t_bool	all_unique_entities_found(t_bool *map);

/*
	returns TRUE if parsing was successful, FALSE if wasn't,
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
	ptrarr_destroy(tokens, destroy_pchar);
	return (stat);
}

int	parse_lines(const t_ptrarr *lines, t_scene *scene)
{
	int		i;
	t_bool	already_found[N_IDENTIFIER_UNIQUE];

	ft_memset(already_found, FALSE, sizeof(already_found));
	i = -1;
	while (++i < lines->len)
	{
		if (parse_unique_entity_loop(already_found, lines->data[i], scene)
			== TRUE)
			continue ;
		if (parse_common_entity(lines->data[i], scene)
			== TRUE)
			continue ;
		return (CODE_ERROR_DATA);
	}
	if (!all_unique_entities_found(already_found))
		return (CODE_ERROR_DATA);
	return (CODE_OK);
}
