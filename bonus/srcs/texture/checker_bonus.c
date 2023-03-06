/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:43:01 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "libft.h"
#include "texture_bonus.h"

void	texture_checker_get_color_at(
			t_texture *self, t_color *out, const t_hit_record *hitrec)
{
	t_texture_checker	*this;
	int					u_scaled;
	int					v_scaled;

	this = (t_texture_checker *)self;
	u_scaled = floor(hitrec->uv.i[0] * this->freq);
	v_scaled = floor(hitrec->uv.i[1] * this->freq);
	if ((u_scaled + v_scaled) % 2 == 0)
		this->a->get_color_at(this->a, out, hitrec);
	else
		this->b->get_color_at(this->b, out, hitrec);
}

t_texture	*texture_checker_create(const char *name,
				t_texture *a, t_texture *b, int freq)
{
	t_texture_checker	*out;

	out = malloc(sizeof(t_texture_checker));
	if (!out)
		return (NULL);
	out->name = ft_strdup(name);
	if (!out->name)
	{
		free(out);
		return (NULL);
	}
	out->destroy = texture_destroy;
	out->get_color_at = texture_checker_get_color_at;
	out->a = a;
	out->b = b;
	out->freq = freq;
	return ((t_texture *)out);
}
