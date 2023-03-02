#include <stdio.h>
#include "mlx.h"
#include "print.h"
#include "mlx_interface.h"

static void	getpixel(t_pixel *p, int x, int y, t_color color)
{
	const t_minmax	in = {0, 1};
	const t_minmax	out = {0, 255};
	int				i;
	int				rgb[3];

	p->x = x;
	p->y = y;
	i = 0;
	while (i < 3)
	{
		rgb[i] = clamp_int(map_minmax(color.i[i], &in, &out), 0, 255);
		i++;
	}
	p->color = rgb[0] << 16 | rgb[1] << 8 | rgb[2];
}

static void	putpixel(t_display *disp, t_imgwrapper *img, int x, int y)
{
	t_uv			uv;
	const t_minmax	out = {0, 1};
	t_color			color;
	t_pixel			p;

	uv.i[0] = map_minmax((double)x, &img->x_range, &out);
	uv.i[1] = map_minmax((double)y, &img->y_range, &out);
	imgwrapper_getcolor(img, &color, &uv);
	getpixel(&p, x, y, color);
	display_putpixel(disp, p);
}

static void	putimage(t_display *disp, t_imgwrapper *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			putpixel(disp, img, x, y);
			x++;
		}
		y++;
	}
	display_putimage(disp);
}

int	main(void)
{
	t_display		*disp;
	t_imgwrapper	*img;

	disp = display_create(100, 100, 10, "");
	img = imgwrapper_create("tests/steve_head_front.xpm");
	putimage(disp, img);
	mlx_loop(mlx_interface_get_mlx_ptr());
	return (0);
}
