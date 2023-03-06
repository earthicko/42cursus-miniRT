/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cylinder_patternmatcher_bonus.c              :+:      :+:    :+:   */
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
#include "builder_internal_bonus.h"

/*
		cy x , y , z   u , v , w   D   H   r  ,  g  ,  b
		0  1 2 3 4 5   6 7 8 9 10  11  12  13 14 15 16 17
	∗ identifier: cy
	∗ x,y,z coordinates of the center of the cylinder
	∗ 3d normalized vector of axis of cylinder
		In range [-1,1] for each x,y,z axis
	∗ the cylinder diameter
	∗ the cylinder height
	∗ R,G,B colors in range [0,255]
*/
t_bool	is_cylinder_with_color(const t_ptrarr *tokens)
{
	static const int	patternlen = 18;
	static const int	pattern[18] = {
		TOKENTYPE_IDENTIFIER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
	};

	if (is_in_pattern(IDENTIFIER_CYLINDER, pattern, patternlen, tokens))
		return (TRUE);
	return (FALSE);
}

/*
		cy x , y , z   u , v , w   D   H   material_name
		0  1 2 3 4 5   6 7 8 9 10  11  12  13
	∗ identifier: cy
	∗ x,y,z coordinates of the center of the cylinder
	∗ 3d normalized vector of axis of cylinder
		In range [-1,1] for each x,y,z axis
	∗ the cylinder diameter
	∗ the cylinder height
	∗ name of material
*/
t_bool	is_cylinder_with_material(const t_ptrarr *tokens)
{
	static const int	patternlen = 14;
	static const int	pattern[14] = {
		TOKENTYPE_IDENTIFIER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER,
		TOKENTYPE_WORD
	};

	if (is_in_pattern(IDENTIFIER_CYLINDER, pattern, patternlen, tokens))
		return (TRUE);
	return (FALSE);
}

t_bool	is_cylinder(const t_ptrarr *tokens)
{
	if (is_cylinder_with_color(tokens) || is_cylinder_with_material(tokens))
		return (TRUE);
	return (FALSE);
}
