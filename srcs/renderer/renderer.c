#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "msgdef.h"
#include "renderer.h"

void	renderer_render_pixel(t_renderer *renderer, int x, int y);
void	renderer_write_color(t_renderer *renderer, int n_samples);

static void	renderer_render_showstat(t_renderer *renderer, int n_samples)
{
	static int			i;
	const static char	*blinker[3] = {".     ", "..    ", "...   "};

	if (n_samples == renderer->n_samples - 1
		|| n_samples % RENDERER_UPDATE_FREQ_SHOW == 0)
	{
		ft_printf("\rSample count %d ", n_samples);
		ft_printf("%s", blinker[(i++) % (sizeof(blinker) / sizeof(char *))]);
	}
}

static void	renderer_render_loop(t_renderer *renderer)
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

static char	*get_filename(int n)
{
	char	*filename;
	char	*postfix;

	postfix = ft_itoa(n);
	if (!postfix)
		return (NULL);
	filename = ft_strmerge(4, OUTPUT_FILENAME, "_", postfix, ".bmp");
	free(postfix);
	if (!filename)
		return (NULL);
	return (filename);
}

static void	renderer_render_flush(t_renderer *renderer, int n_samples)
{
	char	*filename;

	if (n_samples >= renderer->n_samples
		|| n_samples % RENDERER_UPDATE_FREQ_SHOW == 0
		|| n_samples % RENDERER_UPDATE_FREQ_SAVE == 0)
		renderer_write_color(renderer, n_samples);
	if (n_samples >= renderer->n_samples
		|| n_samples % RENDERER_UPDATE_FREQ_SHOW == 0)
		display_putimage(renderer->disp);
	filename = get_filename(n_samples);
	if (!filename)
	{
		ft_dprintf(2, "%s: "MSG_MALLOC, EXEC_NAME);
		return ;
	}
	if (n_samples >= renderer->n_samples
		|| n_samples % RENDERER_UPDATE_FREQ_SAVE == 0)
		display_save_bmp(renderer->disp, filename);
	free(filename);
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
			renderer_render_flush(renderer, n_samples_so_far);
		}
		return (0);
	}
	renderer_render_loop(renderer);
	n_samples_so_far++;
	renderer_render_showstat(renderer, n_samples_so_far);
	renderer_render_flush(renderer, n_samples_so_far);
	return (0);
}
