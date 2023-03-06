#include <stdlib.h>
#include "libft.h"
#include "mlx_interface_bonus.h"
#include "texture_bonus.h"

void	texture_image_destroy(t_texture *self)
{
	if (((t_texture_image *)self)->img)
		imgwrapper_destroy(((t_texture_image *)self)->img);
	if (self->name)
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

t_texture	*texture_image_create(const char *name,
				char *imgpath, int rotation, int flip)
{
	t_texture_image	*out;

	out = malloc(sizeof(t_texture_image));
	if (!out)
		return (NULL);
	ft_bzero(out, sizeof(t_texture_image));
	out->name = ft_strdup(name);
	if (!out->name)
	{
		texture_image_destroy((t_texture *)out);
		return (NULL);
	}
	out->img = imgwrapper_create(imgpath, rotation, flip);
	if (!out->img)
	{
		texture_image_destroy((t_texture *)out);
		return (NULL);
	}
	out->destroy = texture_image_destroy;
	out->get_color_at = texture_image_get_color_at;
	out->imgpath = imgpath;
	return ((t_texture *)out);
}
