#include <stdlib.h>
#include "libft.h"
#include "mlx_interface.h"
#include "texture.h"

void	texture_image_destroy(t_texture *self)
{
	imgwrapper_destroy(((t_texture_image *)self)->img);
	free(self->name);
	free(self);
}

void	texture_image_get_color_at(
			t_texture *self, t_color *out, const t_hit_record *hitrec)
{
	t_texture_image	*this;

	this = (t_texture_image *)self;
	imgwrapper_getcolor(this->img, out, &hitrec->uv);
}

t_texture	*texture_image_create(const char *name, t_imgwrapper *img)
{
	t_texture_image	*out;

	out = malloc(sizeof(t_texture_image));
	if (!out)
		return (NULL);
	out->name = ft_strdup(name);
	if (!out->name)
	{
		free(out);
		return (NULL);
	}
	out->destroy = texture_image_destroy;
	out->get_color_at = texture_image_get_color_at;
	out->img = img;
	return ((t_texture *)out);
}
