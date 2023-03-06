#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "msgdef_bonus.h"
#include "renderer_internal_bonus.h"
#include "settingman_bonus.h"

static t_bool	should_update(int max_samples, int n_samples, int freq)
{
	if (n_samples >= max_samples
		|| n_samples == 1
		|| n_samples % freq == 0)
		return (TRUE);
	return (FALSE);
}

static void	renderer_render_update(t_renderer *renderer, int n_samples)
{
	char		*filename;
	static int	update_count;

	if (should_update(renderer->max_samples, n_samples, renderer->freq_update))
	{
		renderer_write_color(renderer, n_samples);
		display_putimage(renderer->disp);
		update_count++;
	}
	if (should_update(renderer->max_samples, n_samples, renderer->freq_update)
		&& update_count % renderer->freq_save == 0)
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
	if (n_samples_so_far >= renderer->max_samples)
	{
		printf("\nRender finished.\n");
		render_finished = 1;
		timeman(1);
		renderer_render_update(renderer, n_samples_so_far);
		return (0);
	}
	renderer_render_loop(renderer);
	n_samples_so_far++;
	renderer_render_showstat(n_samples_so_far);
	renderer_render_update(renderer, n_samples_so_far);
	return (0);
}
