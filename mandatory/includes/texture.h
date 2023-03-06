/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "hittable.h"
# include "geometry.h"
# include "mlx_interface.h"

typedef struct s_hit_record	t_hit_record;
typedef struct s_texture	t_texture;

typedef void				(*t_texture_get_color_at)(t_texture *self,
		t_color *out, const t_hit_record *hitrec);

typedef struct s_texture
{
	t_texture_get_color_at	get_color_at;
}	t_texture;

typedef struct s_texture_solid
{
	t_texture_get_color_at	get_color_at;
	t_color					color;
}	t_texture_solid;

t_texture	*texture_solid_create(t_color color);

#endif
