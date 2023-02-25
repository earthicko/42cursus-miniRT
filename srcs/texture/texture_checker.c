#include <stdlib.h>
#include "texture_internal.h"

t_texture	*texture_checker_create(t_texture *a, t_texture *b, double freq)
{
	t_texture_checker	*out;

	out = malloc(sizeof(t_texture_checker));
	if (!out)
		return (NULL);
	out->get_color_at = texture_checker_get_color_at;
	out->a = a;
	out->b = b;
	out->freq = freq;
	return ((t_texture *)out);
}

void	texture_checker_get_color_at(
			t_texture *self, t_color *out, const t_hit_record *hitrec)
{
	t_texture_checker	*this;
	int					checker[2];

	this = (t_texture_checker *)self;
	checker[0] = (int)(hitrec->uv.i[0] * this->freq) % 2;
	checker[1] = (int)(hitrec->uv.i[1] * this->freq) % 2;
	if (checker[0] ^ checker[1])
		this->a->get_color_at(this->a, out, hitrec);
	else
		this->b->get_color_at(this->b, out, hitrec);
}
