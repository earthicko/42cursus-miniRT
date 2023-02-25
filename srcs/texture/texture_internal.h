#ifndef TEXTURE_INTERNAL_H
# define TEXTURE_INTERNAL_H

# include "texture.h"

void		texture_solid_get_color_at(
				t_texture *self, t_color *out, const t_hit_record *hitrec);
void		texture_checker_get_color_at(
				t_texture *self, t_color *out, const t_hit_record *hitrec);

#endif
