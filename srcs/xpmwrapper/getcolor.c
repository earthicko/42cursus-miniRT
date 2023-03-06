#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "ptrarr.h"
#include "libft.h"
#include "msgdef.h"
#include "texture.h"

void	xpmwrapper_getcolor(t_xpmwrapper *xpm, t_color *out, const t_uv *uv)
{
	int				x;
	int				y;
	const t_minmax	uv_range = {0, 1};

	x = map_minmax(uv->i[0], &uv_range, &xpm->x_range);
	y = map_minmax(uv->i[1], &uv_range, &xpm->y_range);
	if (x < 0 || x >= xpm->width || y < 0 || y >= xpm->height)
	{
		vec3_setval(out, 0, 0, 0);
		return ;
	}
	*out = xpm->colors[xpm->width * y + x];
}
