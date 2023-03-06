#ifndef TEXTURE_H
# define TEXTURE_H

# include "hittable.h"
# include "geometry.h"
# include "mlx_interface.h"

typedef struct s_hit_record	t_hit_record;
typedef struct s_texture	t_texture;

typedef void				(*t_texture_get_color_at)(t_texture *self,
		t_color *out, const t_hit_record *hitrec);
typedef void				(*t_texture_destroy)(t_texture *self);

typedef struct s_texture
{
	t_texture_destroy		destroy;
	char					*name;
	t_texture_get_color_at	get_color_at;
}	t_texture;

typedef struct s_texture_solid
{
	t_texture_destroy		destroy;
	char					*name;
	t_texture_get_color_at	get_color_at;
	t_color					color;
}	t_texture_solid;

void		texture_destroy(t_texture *self);

t_texture	*texture_solid_create(const char *name, t_color color);

#endif
