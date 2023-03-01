#ifndef BUILDER_INTERNAL_H
# define BUILDER_INTERNAL_H

# include "../parser_internal.h"

int		add_texture_solid(t_scene *scene,
			const char *solid, t_color color);
int		add_material_lambertian(t_scene *scene,
			const char *name, t_texture *texture);
void	map_color(t_color *color);

t_bool	is_ambient_lighting(const t_ptrarr *tokens);
t_bool	is_camera(const t_ptrarr *tokens);
t_bool	is_light(const t_ptrarr *tokens);
t_bool	is_sphere(const t_ptrarr *tokens);
t_bool	is_plane(const t_ptrarr *tokens);
t_bool	is_cylinder(const t_ptrarr *tokens);
t_bool	is_texture_solid(const t_ptrarr *tokens);
t_bool	is_texture_checker(const t_ptrarr *tokens);
t_bool	is_material_lambertian(const t_ptrarr *tokens);

t_bool	is_invalid_ratio(double ratio);
t_bool	is_invalid_length(double len);
t_bool	is_invalid_color(const t_color *color);
t_bool	is_invalid_normalized_vec3(const t_vec3 *vec);
t_bool	is_invalid_fov(double fov);

void	build_vector(t_vec3 *out, const void **token_start);

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
int		build_texture_solid(
			const t_ptrarr *tokens, t_scene *scene);
int		build_texture_checker(
			const t_ptrarr *tokens, t_scene *scene);
int		build_material_lambertian(
			const t_ptrarr *tokens, t_scene *scene);

#endif
