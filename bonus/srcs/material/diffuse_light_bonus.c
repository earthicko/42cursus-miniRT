/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse_light_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "material_internal_bonus.h"

t_material	*material_diffuse_light_create(const char *name, t_texture *emitter)
{
	t_material_diffuse_light	*out;

	out = malloc(sizeof(t_material_diffuse_light));
	if (!out)
		return (NULL);
	out->name = ft_strdup(name);
	if (!out->name)
	{
		free(out);
		return (NULL);
	}
	out->destroy = material_destroy;
	out->emit = material_diffuse_light_emit;
	out->scatter = material_diffuse_light_scatter;
	out->emitter = emitter;
	return ((t_material *)out);
}

void	material_diffuse_light_emit(
		t_material *self, t_color *out, const t_hit_record *hitrec)
{
	t_material_diffuse_light	*this;

	this = (t_material_diffuse_light *)self;
	this->emitter->get_color_at(this->emitter, out, hitrec);
}

t_bool	material_diffuse_light_scatter(
			t_material *self,
			t_scatter_record *out,
			const t_ray *ray_in,
			const t_hit_record *hit)
{
	(void)self;
	(void)out;
	(void)ray_in;
	(void)hit;
	return (FALSE);
}
