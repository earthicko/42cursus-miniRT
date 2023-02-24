#ifndef TEXTURE_H
# define TEXTURE_H

# include "geometry.h"

typedef struct s_texture	t_texture;

typedef void				(*t_texture_get_color_at)(t_texture *self,
		t_color *out, const t_uv *uv, const t_vec3 *p);

typedef struct s_texture
{
	t_texture_get_color_at	get_color_at;
}	t_texture;

typedef struct s_texture_solid
{
	t_texture_get_color_at	get_color_at;
	t_color					color;
}	t_texture_solid;

typedef struct s_texture_checker
{
	t_texture_get_color_at	get_color_at;
	t_texture				*a;
	t_texture				*b;
	double					freq;
}	t_texture_checker;

t_texture	*texture_solid_create(t_color color);
t_texture	*texture_checker_create(t_texture *a, t_texture *b, double freq);

#endif
