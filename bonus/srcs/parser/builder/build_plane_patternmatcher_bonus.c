/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_plane_patternmatcher_bonus.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "print_bonus.h"
#include "builder_internal_bonus.h"

/*
		pl x , y , z   u , v , w   scale  r  ,  g  ,  b
		0  1 2 3 4 5   6 7 8 9 10  11     12 13 14 15 16
	∗ identifier: pl
	∗ x,y,z coordinates of a point in the plane
	∗ 3d normalized normal vector.
		In range [-1,1] for each x,y,z axis
	∗ scale value to be used in texture mapping
	∗ R,G,B colors in range [0-255]
*/
t_bool	is_plane_with_color(const t_ptrarr *tokens)
{
	static const int	patternlen = 17;
	static const int	pattern[17] = {
		TOKENTYPE_IDENTIFIER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER
	};

	if (is_in_pattern(IDENTIFIER_PLANE, pattern, patternlen, tokens))
		return (TRUE);
	return (FALSE);
}

/*
		pl x , y , z   u , v , w   scale  material_name
		0  1 2 3 4 5   6 7 8 9 10  11     12
	∗ identifier: pl
	∗ x,y,z coordinates of a point in the plane
	∗ 3d normalized normal vector.
		In range [-1,1] for each x,y,z axis
	∗ scale value to be used in texture mapping
	∗ name of material
*/
t_bool	is_plane_with_material(const t_ptrarr *tokens)
{
	static const int	patternlen = 13;
	static const int	pattern[13] = {
		TOKENTYPE_IDENTIFIER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER,
		TOKENTYPE_WORD
	};

	if (is_in_pattern(IDENTIFIER_PLANE, pattern, patternlen, tokens))
		return (TRUE);
	return (FALSE);
}

t_bool	is_plane(const t_ptrarr *tokens)
{
	if (is_plane_with_color(tokens) || is_plane_with_material(tokens))
		return (TRUE);
	return (FALSE);
}
