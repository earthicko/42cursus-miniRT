#ifndef XPMWRAPPER_H
# define XPMWRAPPER_H

# include "geometry.h"
# include "number.h"

typedef struct s_xpmwrapper
{
	int			width;
	int			height;
	t_minmax	x_range;
	t_minmax	y_range;
	t_color		*colors;
}	t_xpmwrapper;

t_xpmwrapper	*xpmwrapper_create(const char *filename,
					int rotation, int flip);
void			xpmwrapper_destroy(t_xpmwrapper *xpm);
void			xpmwrapper_getcolor(t_xpmwrapper *xpm,
					t_color *out, const t_uv *uv);

#endif
