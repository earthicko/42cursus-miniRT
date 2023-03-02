#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "msgdef.h"
#include "renderer.h"
#include "settingman.h"

void	renderer_render_pixel(t_renderer *renderer, int x, int y);
void	renderer_write_color(t_renderer *renderer, int n_samples);

static void	renderer_render_showstat(t_renderer *renderer, int n_samples)
{
	static int			i;
	const static char	*blinker[3] = {".     ", "..    ", "...   "};

	if (n_samples == renderer->n_samples - 1
		|| n_samples % renderer->freq_save == 0)
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

static void	renderer_render_update(t_renderer *renderer, int n_samples)
{
	char	*filename;

	if (n_samples >= renderer->n_samples
		|| n_samples == 1
		|| n_samples % renderer->freq_update == 0
		|| n_samples % renderer->freq_save == 0)
		renderer_write_color(renderer, n_samples);
	if (n_samples >= renderer->n_samples
		|| n_samples == 1
		|| n_samples % renderer->freq_update == 0)
		display_putimage(renderer->disp);
	if (n_samples >= renderer->n_samples
		|| n_samples % renderer->freq_save == 0)
	{
		filename = get_filename(n_samples);
		if (!filename)
		{
			printf("%s: "MSG_MALLOC, EXEC_NAME);
			return ;
		}
		display_save_bmp(renderer->disp, filename);
		free(filename);
	}
}

void	timeman(int mode);

// TODO: remove timeman before submission
int	renderer_render(void *param)
{
	t_renderer	*renderer;
	static int	n_samples_so_far;
	static int	render_finished;

	renderer = (t_renderer *)param;
	if (render_finished == 1)
		return (0);
	if (n_samples_so_far == 0)
		timeman(0);
	if (n_samples_so_far >= renderer->n_samples)
	{
		printf("\nRender finished.\n");
		render_finished = 1;
		timeman(1);
		renderer_render_update(renderer, n_samples_so_far);
		return (0);
	}
	renderer_render_loop(renderer);
	n_samples_so_far++;
	renderer_render_showstat(renderer, n_samples_so_far);
	renderer_render_update(renderer, n_samples_so_far);
	return (0);
}
