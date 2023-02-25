#include <stdlib.h>
#include "texture_internal.h"

t_texture	*texture_solid_create(t_color color)
{
	t_texture_solid	*out;

	out = malloc(sizeof(t_texture_solid));
	if (!out)
		return (NULL);
	out->get_color_at = texture_solid_get_color_at;
	out->color = color;
	return ((t_texture *)out);
}

void	texture_solid_get_color_at(
			t_texture *self, t_color *out, const t_hit_record *hitrec)
{
	(void)hitrec;
	*out = ((t_texture_solid *)self)->color;
}
