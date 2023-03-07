/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_BONUS_H
# define MATERIAL_BONUS_H

# include "geometry_bonus.h"
# include "ray_bonus.h"
# include "hittable_bonus.h"
# include "texture_bonus.h"

typedef struct s_hit_record	t_hit_record;
typedef struct s_material	t_material;
typedef struct s_texture	t_texture;

typedef struct s_scatter_record
{
	t_color	albedo;
	t_ray	scattered;
}	t_scatter_record;

typedef void				(*t_material_destroy)(t_material *self);

typedef void				(*t_material_emit)(t_material *self,
	t_color *out, const t_hit_record *hitrec);

typedef t_bool				(*t_material_scatter)(t_material *self,
	t_scatter_record *out, const t_ray *ray_in, const t_hit_record *hit);

typedef struct s_material
{
	t_material_destroy	destroy;
	t_material_emit		emit;
	t_material_scatter	scatter;
	char				*name;
}	t_material;

typedef struct s_material_lambertian
{
	t_material_destroy	destroy;
	t_material_emit		emit;
	t_material_scatter	scatter;
	char				*name;
	t_texture			*albedo;
}	t_material_lambertian;

typedef struct s_material_metal
{
	t_material_destroy	destroy;
	t_material_emit		emit;
	t_material_scatter	scatter;
	char				*name;
	t_texture			*albedo;
	double				fuzz;
}	t_material_metal;

typedef struct s_material_dielectric
{
	t_material_destroy	destroy;
	t_material_emit		emit;
	t_material_scatter	scatter;
	char				*name;
	double				ior;
}	t_material_dielectric;

typedef struct s_material_diffuse_light
{
	t_material_destroy	destroy;
	t_material_emit		emit;
	t_material_scatter	scatter;
	char				*name;
	t_texture			*emitter;
}	t_material_diffuse_light;

void		material_destroy(t_material *self);

t_material	*material_lambertian_create(const char *name,
				t_texture *albedo);
t_material	*material_metal_create(const char *name,
				t_texture *albedo, double fuzz);
t_material	*material_dielectric_create(const char *name,
				double ior);
t_material	*material_diffuse_light_create(const char *name,
				t_texture *emitter);

#endif