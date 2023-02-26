#include "renderer.h"
#include "number.h"

static void	map_pixel_color(int *rgb, t_renderer *renderer, t_pixel *p, int n)
{
	const t_minmax	in = {0, n + 1};
	const t_minmax	out = {0, 255};
	int				i;

	i = 0;
	while (i < 3)
	{
		rgb[i] = map_minmax(renderer->disp->colors[
				(renderer->disp->w * (renderer->disp->h - p->y - 1))
				+ p->x].i[i], &in, &out);
		rgb[i] = clamp_int(rgb[i], 0, 255);
		i++;
	}
}

// TODO: gamma correction, NaN filtering
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
