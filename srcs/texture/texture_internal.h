#ifndef TEXTURE_INTERNAL_H
# define TEXTURE_INTERNAL_H

# include "texture.h"

void		texture_solid_get_color_at(
				t_texture *self, t_color *out, const t_uv *uv, const t_vec3 *p);
void		texture_checker_get_color_at(
				t_texture *self, t_color *out, const t_uv *uv, const t_vec3 *p);

#endif
