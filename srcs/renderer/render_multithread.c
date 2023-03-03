#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "msgdef.h"
#include "renderer_internal.h"
#include "settingman.h"

static void	renderer_render_update(t_renderer *renderer, int n_samples)
{
	char		*filename;
	static int	update_count;

	if (n_samples == 0)
		return ;
	renderer_write_color(renderer, n_samples);
	display_putimage(renderer->disp);
	update_count++;
	if (update_count % renderer->freq_save == 0
		|| renderer->max_samples == n_samples)
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

static void	set_next_milestone(t_renderer *renderer,
				t_renderer_supervisor *stat)
{
	int	curr_milestone;
	int	next_milestone;

	curr_milestone = milestone(stat);
	next_milestone = get_next_milestone(renderer, curr_milestone);
	renderer_render_update(renderer, curr_milestone);
	set_n_samples_main(stat, curr_milestone);
	set_milestone(stat, next_milestone);
}

void	timeman(int mode);

// TODO: remove timeman before submission
int	renderer_render_multithreaded(void *param)
{
	t_renderer						*renderer;
	static t_renderer_supervisor	stat;
	static int						init;

	renderer = (t_renderer *)param;
	if (init == 0)
	{
		if (init_workers(renderer, &stat))
			return (1);
		init = 1;
	}
	if (is_render_finished(&stat))
		return (0);
	if (n_samples_main(&stat) >= renderer->max_samples)
	{
		terminate_workers(&stat);
		renderer_render_update(renderer, n_samples_main(&stat));
		return (0);
	}
	if (all_workers_reach_milestone(&stat))
		set_next_milestone(renderer, &stat);
	sleep(RENDER_SYNC_INTERVAL);
	return (0);
}
