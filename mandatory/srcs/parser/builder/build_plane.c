/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:46:38 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "builder_internal.h"

/*
		pl x , y , z   u , v , w   r  ,  g  ,  b
		0  1 2 3 4 5   6 7 8 9 10  11 12 13 14 15
	∗ identifier: pl
	∗ x,y,z coordinates of a point in the plane
	∗ 3d normalized normal vector.
		In range [-1,1] for each x,y,z axis
	∗ R,G,B colors in range [0-255]
*/
t_bool	is_plane(const t_ptrarr *tokens)
{
	static const int	patternlen = 16;
	static const int	pattern[16] = {
		TOKENTYPE_IDENTIFIER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER
	};

	if (is_in_pattern(IDENTIFIER_PLANE, pattern, patternlen, tokens))
		return (TRUE);
	return (FALSE);
}

static int	add_plane(t_scene *scene, t_ray dir, t_material *m)
{
	t_hittable	*plane;

	plane = hittable_plane_create(dir.orig, dir.dir, m);
	if (!plane)
		return (CODE_ERROR_MALLOC);
	if (ptrarr_append(scene->res.primitives, plane))
	{
		free(plane);
		return (CODE_ERROR_MALLOC);
	}
	if (hittable_list_append(scene->world, plane)
		|| hittable_list_append(scene->objects, plane))
		return (CODE_ERROR_MALLOC);
	return (CODE_OK);
}

int	build_plane(const t_ptrarr *tokens, t_scene *scene)
{
	t_ray	dir;
	t_color	color;

	build_vector(&dir.orig, &tokens->data[1]);
	build_vector(&dir.dir, &tokens->data[6]);
	build_vector(&color, &tokens->data[11]);
	if (is_invalid_normalized_vec3(&dir.dir) || is_invalid_color(&color))
		return (CODE_ERROR_DATA);
	vec3_unitize(&dir.dir);
	map_color(&color);
	if (add_texture_solid(scene, color))
		return (CODE_ERROR_MALLOC);
	if (add_material_lambertian(scene, ptrarr_getlast(scene->res.textures)))
		return (CODE_ERROR_MALLOC);
	if (add_plane(scene, dir, ptrarr_getlast(scene->res.materials)))
		return (CODE_ERROR_MALLOC);
	return (CODE_OK);
}
