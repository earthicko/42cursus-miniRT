/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder_internal_bonus.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDER_INTERNAL_BONUS_H
# define BUILDER_INTERNAL_BONUS_H

# include "../parser_internal_bonus.h"

int		add_texture_solid(t_scene *scene,
			const char *solid, t_color color);
int		add_material_lambertian(t_scene *scene,
			const char *name, t_texture *texture);
void	map_color(t_color *color);

t_bool	is_setting_display(const t_ptrarr *tokens);
t_bool	is_setting_camera(const t_ptrarr *tokens);
t_bool	is_setting_renderer(const t_ptrarr *tokens);
t_bool	is_ambient_lighting(const t_ptrarr *tokens);
t_bool	is_camera(const t_ptrarr *tokens);
t_bool	is_light(const t_ptrarr *tokens);
t_bool	is_sphere(const t_ptrarr *tokens);
t_bool	is_plane(const t_ptrarr *tokens);
t_bool	is_cylinder(const t_ptrarr *tokens);
t_bool	is_cone(const t_ptrarr *tokens);
t_bool	is_box(const t_ptrarr *tokens);
t_bool	is_texture_solid(const t_ptrarr *tokens);
t_bool	is_texture_checker(const t_ptrarr *tokens);
t_bool	is_texture_image(const t_ptrarr *tokens);
t_bool	is_material_lambertian(const t_ptrarr *tokens);
t_bool	is_material_metal(const t_ptrarr *tokens);
t_bool	is_material_dielectric(const t_ptrarr *tokens);
t_bool	is_material_diffuse_light(const t_ptrarr *tokens);

t_bool	is_invalid_ratio(double ratio);
t_bool	is_invalid_length(double len);
t_bool	is_invalid_color(const t_color *color);
t_bool	is_invalid_normalized_vec3(const t_vec3 *vec);
t_bool	is_invalid_fov(double fov);

void	build_vector(t_vec3 *out, const void **token_start);

int		build_setting_display(
			const t_ptrarr *tokens, t_scene *scene);
int		build_setting_camera(
			const t_ptrarr *tokens, t_scene *scene);
int		build_setting_renderer(
			const t_ptrarr *tokens, t_scene *scene);
int		build_ambient_lighting(
			const t_ptrarr *tokens, t_scene *scene);
int		build_camera(
			const t_ptrarr *tokens, t_scene *scene);
int		build_light(
			const t_ptrarr *tokens, t_scene *scene);
int		build_sphere(
			const t_ptrarr *tokens, t_scene *scene);
int		build_plane(
			const t_ptrarr *tokens, t_scene *scene);
int		build_cylinder(
			const t_ptrarr *tokens, t_scene *scene);
int		build_cone(
			const t_ptrarr *tokens, t_scene *scene);
int		build_box(
			const t_ptrarr *tokens, t_scene *scene);
int		build_texture_solid(
			const t_ptrarr *tokens, t_scene *scene);
int		build_texture_checker(
			const t_ptrarr *tokens, t_scene *scene);
int		build_texture_image(
			const t_ptrarr *tokens, t_scene *scene);
int		build_material_lambertian(
			const t_ptrarr *tokens, t_scene *scene);
int		build_material_metal(
			const t_ptrarr *tokens, t_scene *scene);
int		build_material_dielectric(
			const t_ptrarr *tokens, t_scene *scene);
int		build_material_diffuse_light(
			const t_ptrarr *tokens, t_scene *scene);

#endif
