#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "msgdef.h"
#include "xpmwrapper.h"
#include "texture.h"

void	texture_image_destroy(t_texture *self)
{
	if (((t_texture_image *)self)->xpm)
		xpmwrapper_destroy(((t_texture_image *)self)->xpm);
	if (self->name)
		free(self->name);
	free(self);
}

void	texture_image_get_color_at(
			t_texture *self, t_color *out, const t_hit_record *hitrec)
{
	t_texture_image	*this;

	this = (t_texture_image *)self;
	xpmwrapper_getcolor(this->xpm, out, &hitrec->uv);
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
	out->xpm = xpmwrapper_create(imgpath, rotation, flip);
	if (!out->xpm)
	{
		printf("%s: Failed to load image %s.\n", EXEC_NAME, imgpath);
		texture_image_destroy((t_texture *)out);
		return (NULL);
	}
	out->destroy = texture_image_destroy;
	out->get_color_at = texture_image_get_color_at;
	return ((t_texture *)out);
}
