/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:46:24 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "number.h"
#include "builder_internal.h"

/*
		sp x , y , z   D   r  ,  g  ,  b
		0  1 2 3 4 5   6   7  8  9  10 11
	∗ identifier: sp
	∗ x,y,z coordinates of the sphere center
	∗ the sphere diameter
	∗ R,G,B colors in range [0-255]
*/
t_bool	is_sphere(const t_ptrarr *tokens)
{
	static const int	patternlen = 12;
	static const int	pattern[12] = {
		TOKENTYPE_IDENTIFIER,
		TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA,
		TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA,
		TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA,
		TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA,
		TOKENTYPE_NUMBER
	};

	if (is_in_pattern(IDENTIFIER_SPHERE, pattern, patternlen, tokens))
		return (TRUE);
	return (FALSE);
}

static int	add_sphere(t_scene *scene, t_point cen, double d, t_material *m)
{
	t_hittable	*sphere;

	sphere = hittable_sphere_create(cen, d / 2, m);
	if (!sphere)
		return (CODE_ERROR_MALLOC);
	if (ptrarr_append(scene->res.primitives, sphere))
	{
		free(sphere);
		return (CODE_ERROR_MALLOC);
	}
	if (hittable_list_append(scene->world, sphere)
		|| hittable_list_append(scene->objects, sphere))
		return (CODE_ERROR_MALLOC);
	return (CODE_OK);
}

int	build_sphere(const t_ptrarr *tokens, t_scene *scene)
{
	t_point		cen;
	double		d;
	t_color		color;

	build_vector(&cen, &tokens->data[1]);
	d = ft_atof(tokens->data[6]);
	build_vector(&color, &tokens->data[7]);
	if (is_invalid_length(d / 2) || is_invalid_color(&color))
		return (CODE_ERROR_DATA);
	map_color(&color);
	if (add_texture_solid(scene, "", color))
		return (CODE_ERROR_MALLOC);
	if (add_material_lambertian(scene, "", ptrarr_getlast(scene->res.textures)))
		return (CODE_ERROR_MALLOC);
	if (add_sphere(scene, cen, d, ptrarr_getlast(scene->res.materials)))
		return (CODE_ERROR_MALLOC);
	return (CODE_OK);
}
