#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "ptrarr.h"
#include "libft.h"
#include "msgdef.h"
#include "texture.h"

static void	xpmwrapper_flip(t_xpmwrapper *xpm)
{
	t_color	buf;
	int		x;
	int		y;

	y = 0;
	while (y < xpm->height)
	{
		x = 0;
		while (x < xpm->width / 2)
		{
			buf = xpm->colors[xpm->width * y + x];
			xpm->colors[xpm->width * y + x]
				= xpm->colors[xpm->width * y + (xpm->width - x - 1)];
			xpm->colors[xpm->width * y + (xpm->width - x - 1)] = buf;
			x++;
		}
		y++;
	}
}

static void	rotate_loop(t_xpmwrapper *xpm, t_color *buf)
{
	int		x;
	int		y;

	y = 0;
	while (y < xpm->height)
	{
		x = 0;
		while (x < xpm->width)
		{
			buf[xpm->height * x + (xpm->height - y - 1)]
				= xpm->colors[xpm->width * y + x];
			x++;
		}
		y++;
	}
}

static int	xpmwrapper_rotate(t_xpmwrapper *xpm)
{
	t_color		*buf;
	int			temp_i;
	t_minmax	temp_m;

	buf = malloc(sizeof(t_color) * xpm->width * xpm->height);
	if (!buf)
		return (CODE_ERROR_MALLOC);
	rotate_loop(xpm, buf);
	temp_i = xpm->width;
	xpm->width = xpm->height;
	xpm->height = temp_i;
	temp_m = xpm->x_range;
	xpm->x_range = xpm->y_range;
	xpm->y_range = temp_m;
	free(xpm->colors);
	xpm->colors = buf;
	return (CODE_OK);
}

int	xpmwrapper_transform(t_xpmwrapper *xpmwrapper, int rotation, int flip)
{
	int	i;

	if (flip)
		xpmwrapper_flip(xpmwrapper);
	while (rotation < 0)
		rotation += 4;
	i = 0;
	while (i < rotation % 4)
	{
		if (xpmwrapper_rotate(xpmwrapper))
			return (CODE_ERROR_MALLOC);
		i++;
	}
	return (CODE_OK);
}
