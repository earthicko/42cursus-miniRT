/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_texture_image_bonus.c                        :+:      :+:    :+:   */
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

static t_bool	match_extension(const char *path, const char *ext)
{
	size_t	start;

	start = ft_strlen(path) - ft_strlen(ext);
	if (ft_strncmp(path + start, ext, ft_strlen(ext) + 1) == 0)
		return (TRUE);
	return (FALSE);
}

/*
		tx_image <name> <file_name.xpm> rotation flip
		0        1      2               3        4
	∗ identifier: tx image
	∗ name: aarbitary given name of the texture
	∗ file path of the texture image
	∗ rotation: number of 90 deg clockwise rotation to apply
	∗ flip: number of horizontal flips to apply
*/
t_bool	is_texture_image(const t_ptrarr *tokens)
{
	static const int	patternlen = 5;
	static const int	pattern[5] = {
		TOKENTYPE_IDENTIFIER,
		TOKENTYPE_WORD,
		TOKENTYPE_WORD,
		TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER,
	};

	if (is_in_pattern(IDENTIFIER_TEXTURE_IMAGE, pattern, patternlen, tokens)
		&& match_extension(tokens->data[2], ".xpm"))
		return (TRUE);
	return (FALSE);
}

static int	add_texture_image(t_scene *scene,
				const char *name, char *filepath, int transform[2])
{
	t_texture	*image;

	image = texture_image_create(name, filepath, transform[0], transform[1]);
	if (!image)
		return (CODE_ERROR_MALLOC);
	if (ptrarr_append(scene->res.textures, image))
	{
		texture_destroy(image);
		return (CODE_ERROR_MALLOC);
	}
	return (CODE_OK);
}

int	build_texture_image(const t_ptrarr *tokens, t_scene *scene)
{
	int	transform[2];

	transform[0] = (int)ft_atof(tokens->data[3]);
	transform[1] = (int)ft_atof(tokens->data[4]);
	if (add_texture_image(scene,
			tokens->data[1], (char *)tokens->data[2], transform))
		return (CODE_ERROR_MALLOC);
	printf("%s: image texture (%s, using file %s, %d rotation, flip %d)\n",
		__func__,
		((t_texture *)ptrarr_getlast(scene->res.textures))->name,
		(char *)tokens->data[2],
		transform[0], transform[1]);
	return (CODE_OK);
}
