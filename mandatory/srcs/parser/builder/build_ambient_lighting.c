/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ambient_lighting.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:45:48 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "builder_internal.h"

/*
		A 0.2 255,255,255
	∗ identifier: A
	∗ ambient lighting ratio in range [0.0,1.0]: 0.2
	∗ R,G,B colors in range [0-255]: 255, 255, 255
*/
t_bool	is_ambient_lighting(const t_ptrarr *tokens)
{
	static const int	patternlen = 7;
	static const int	pattern[7] = {
		TOKENTYPE_IDENTIFIER,
		TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA,
		TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA,
		TOKENTYPE_NUMBER
	};

	if (is_in_pattern(IDENTIFIER_AMBIENTLIGHTING, pattern, patternlen, tokens))
		return (TRUE);
	return (FALSE);
}

int	build_ambient_lighting(const t_ptrarr *tokens, t_scene *scene)
{
	double	ratio;
	t_vec3	color;

	ratio = ft_atof(tokens->data[1]);
	if (is_invalid_ratio(ratio))
		return (CODE_ERROR_DATA);
	build_vector(&color, &tokens->data[2]);
	if (is_invalid_color(&color))
		return (CODE_ERROR_DATA);
	map_color(&color);
	vec3_mult_num(&scene->bg, &color, ratio);
	return (CODE_OK);
}
