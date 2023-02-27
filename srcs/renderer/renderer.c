#include <stdio.h>
#include "libft.h"
#include "renderer.h"

void	renderer_render_pixel(t_renderer *renderer, int x, int y);
void	renderer_write_color(t_renderer *renderer, int n_samples);

static void	renderer_render_loop(t_renderer *renderer, int n_samples_so_far)
{
	int					x;
	int					y;
	static int			i;
	const static char	*blinker[3] = {".     ", "..    ", "...   "};

	if (n_samples_so_far == renderer->n_samples - 1
		|| n_samples_so_far % RENDERER_UPDATE_FREQ == 0)
	{
		ft_printf("\rSample count %d ", n_samples_so_far);
		ft_printf("%s", blinker[(i++) % (sizeof(blinker) / sizeof(char *))]);
	}
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

int	renderer_render(void *param)
{
	t_renderer	*renderer;
	static int	n_samples_so_far;
	static int	render_finished;

	renderer = (t_renderer *)param;
	if (n_samples_so_far >= renderer->n_samples)
	{
		if (!render_finished)
		{
			printf("\nRender finished.\n");
			render_finished = 1;
			renderer_write_color(renderer, n_samples_so_far);
			display_putimage(renderer->disp);
			display_save_bmp(renderer->disp, "out.bmp");
		}
		return (0);
	}
	renderer_render_loop(renderer, n_samples_so_far);
	if (n_samples_so_far % RENDERER_UPDATE_FREQ == 0)
	{
		renderer_write_color(renderer, n_samples_so_far);
		display_putimage(renderer->disp);
	}
	n_samples_so_far++;
	return (0);
}
