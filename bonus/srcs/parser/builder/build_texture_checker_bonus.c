/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_texture_checker_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "print_bonus.h"
#include "msgdef_bonus.h"
#include "builder_internal_bonus.h"

/*
		tx_checker <name> <pattern 1> <pattern 2> freq
		0          1      2           3           4
	∗ identifier: tx checker
	∗ name: arbitary given name of the texture
	∗ pattern 1: name of other texture that appears first
	∗ pattern 2: name of other texture that appears second
	∗ freq: frequency of the pattern
*/
t_bool	is_texture_checker(const t_ptrarr *tokens)
{
	static const int	patternlen = 5;
	static const int	pattern[5] = {
		TOKENTYPE_IDENTIFIER,
		TOKENTYPE_WORD, TOKENTYPE_WORD, TOKENTYPE_WORD,
		TOKENTYPE_NUMBER
	};

	if (is_in_pattern(IDENTIFIER_TEXTURE_CHECKER, pattern, patternlen, tokens))
		return (TRUE);
	return (FALSE);
}

static int	add_texture_checker(t_scene *scene, const char *name,
				t_texture *(pattern[2]), int freq)
{
	t_texture	*checker;

	checker = texture_checker_create(name, pattern[0], pattern[1], freq);
	if (!checker)
		return (CODE_ERROR_MALLOC);
	if (ptrarr_append(scene->res.textures, checker))
	{
		texture_destroy(checker);
		return (CODE_ERROR_MALLOC);
	}
	return (CODE_OK);
}

int	build_texture_checker(const t_ptrarr *tokens, t_scene *scene)
{
	char		*name;
	t_texture	*pattern[2];
	int			freq;

	name = (char *)(tokens->data[1]);
	pattern[0] = scene_search_texture(scene, tokens->data[2]);
	pattern[1] = scene_search_texture(scene, tokens->data[3]);
	freq = (int)ft_atof(tokens->data[4]);
	if (freq < 2 || freq % 2 == 1)
	{
		printf("%s: invalid frequency (%d).\n", EXEC_NAME, freq);
		return (CODE_ERROR_DATA);
	}
	if (!pattern[0] || !pattern[1])
		return (CODE_ERROR_DATA);
	if (add_texture_checker(scene, name, pattern, freq))
		return (CODE_ERROR_MALLOC);
	printf("%s: checker texture (%s, %s <-> %s %d)\n", __func__, name,
		pattern[0]->name, pattern[1]->name, freq);
	return (CODE_OK);
}
