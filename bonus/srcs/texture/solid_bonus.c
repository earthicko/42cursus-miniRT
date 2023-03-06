/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solid_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "texture_bonus.h"

void	texture_solid_get_color_at(
			t_texture *self, t_color *out, const t_hit_record *hitrec)
{
	(void)hitrec;
	*out = ((t_texture_solid *)self)->color;
}

t_texture	*texture_solid_create(const char *name, t_color color)
{
	t_texture_solid	*out;

	out = malloc(sizeof(t_texture_solid));
	if (!out)
		return (NULL);
	out->name = ft_strdup(name);
	if (!out->name)
	{
		free(out);
		return (NULL);
	}
	out->destroy = texture_destroy;
	out->get_color_at = texture_solid_get_color_at;
	out->color = color;
	return ((t_texture *)out);
}
