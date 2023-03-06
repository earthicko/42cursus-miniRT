/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_material_dielectric_bonus.c                  :+:      :+:    :+:   */
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
		mt_dielectric <name> <IOR>
		0             1      2
	∗ identifier: mt_dielectric
	∗ name: arbitary given name of the material
	∗ IOR: IOR value
*/
t_bool	is_material_dielectric(const t_ptrarr *tokens)
{
	static const int	patternlen = 3;
	static const int	pattern[3] = {
		TOKENTYPE_IDENTIFIER,
		TOKENTYPE_WORD,
		TOKENTYPE_WORD
	};

	if (is_in_pattern(IDENTIFIER_MATERIAL_DIELECTRIC,
			pattern, patternlen, tokens))
		return (TRUE);
	return (FALSE);
}

static int	add_material_dielectric(t_scene *scene,
									const char *name, double ior)
{
	t_material	*dielectric;

	dielectric = material_dielectric_create(name, ior);
	if (!dielectric)
		return (CODE_ERROR_MALLOC);
	if (ptrarr_append(scene->res.materials, dielectric))
	{
		dielectric->destroy(dielectric);
		return (CODE_ERROR_MALLOC);
	}
	return (CODE_OK);
}

int	build_material_dielectric(const t_ptrarr *tokens, t_scene *scene)
{
	const char				*name = tokens->data[1];
	const double			ior = ft_atof(tokens->data[2]);
	t_material_dielectric	*dielectric;

	if (ior < 1)
	{
		printf("%s: IOR "MSG_OUTOFRANGE"\n", EXEC_NAME,
			ior, 1.0, DOUBLE_INF);
	}
	if (add_material_dielectric(scene, name, ior))
		return (CODE_ERROR_MALLOC);
	dielectric = (t_material_dielectric *)ptrarr_getlast(scene->res.materials);
	printf("%s: dielectric material (%s, IOR %.2f)\n", __func__,
		dielectric->name, dielectric->ior);
	return (CODE_OK);
}
