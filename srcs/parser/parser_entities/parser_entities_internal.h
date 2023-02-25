#ifndef PARSER_ENTITIES_INTERNAL_H
# define PARSER_ENTITIES_INTERNAL_H

# include "../parser_internal.h"

int	add_texture_solid(t_scene *scene, t_color color);
int	add_material_lambertian(t_scene *scene, t_texture *texture);

#endif
