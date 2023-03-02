#include "renderer_internal.h"

void	renderer_render_loop_multithread(t_renderer_worker *worker)
{
	int	x;
	int	y;

	y = worker->y_begin;
	while (y < worker->y_end)
	{
		x = 0;
		while (x < worker->renderer->disp->w)
		{
			renderer_render_pixel(worker->renderer, x, y);
			x++;
		}
		y++;
	}
}

void	renderer_render_loop(t_renderer *renderer)
{
	int	x;
	int	y;

	y = 0;
	while (y < renderer->disp->h)
	{
		x = 0;
		while (x < renderer->disp->w)
		{
			renderer_render_pixel(renderer, x, y);
			x++;
		}
		y++;
	}
}
