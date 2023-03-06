#include <math.h>
#include "renderer_bonus.h"
#include "number_bonus.h"

static void	map_pixel_color(int *rgb, t_renderer *renderer, t_pixel *p, int n)
{
	const t_minmax	in = {0, 1};
	const t_minmax	out = {0, 255};
	int				i;
	int				pixel_i;
	double			val;

	i = 0;
	while (i < 3)
	{
		pixel_i = (renderer->disp->w * (renderer->disp->h - p->y - 1)) + p->x;
		val = renderer->disp->colors[pixel_i].i[i];
		if (val != val)
			val = 0.0;
		val /= n;
		val = sqrt(val);
		val = map_minmax(val, &in, &out);
		rgb[i] = clamp_int(val, 0, 255);
		i++;
	}
}

void	renderer_write_color(t_renderer *renderer, int n_samples)
{
	t_pixel			p;
	int				rgb[3];

	p.y = 0;
	while (p.y < renderer->disp->h)
	{
		p.x = 0;
		while (p.x < renderer->disp->w)
		{
			map_pixel_color(rgb, renderer, &p, n_samples);
			p.color = rgb[0] << 16 | rgb[1] << 8 | rgb[2];
			display_putpixel(renderer->disp, p);
			p.x++;
		}
		p.y++;
	}
}
