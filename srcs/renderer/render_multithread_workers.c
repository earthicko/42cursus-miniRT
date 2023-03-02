#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "msgdef.h"
#include "renderer_internal.h"
#include "settingman.h"

void	*worker_routine(void *arg)
{
	t_renderer_worker		*worker;
	t_renderer_supervisor	*stat;
	int						current_n_samples;

	worker = (t_renderer_worker *)arg;
	stat = worker->super;
	while (TRUE)
	{
		if (is_render_finished(stat))
			break ;
		current_n_samples = n_samples_worker(stat, worker->i);
		if (current_n_samples == milestone(stat))
		{
			sleep(RENDER_SYNC_INTERVAL);
			continue ;
		}
		renderer_render_loop_multithread(worker);
		set_n_samples_worker(stat, worker->i, current_n_samples + 1);
	}
	return (NULL);
}

static int	set_worker_info(int h,
				t_renderer *renderer, t_renderer_supervisor *stat)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while (i < RENDER_WORKER_N)
	{
		stat->workers[i].super = stat;
		stat->workers[i].renderer = renderer;
		stat->workers[i].i = i;
		ret |= pthread_mutex_init(&stat->workers[i].m_n_samples, NULL);
		if (i == 0)
			stat->workers[i].y_begin = 0;
		else
			stat->workers[i].y_begin = stat->workers[i - 1].y_end;
		if (i == RENDER_WORKER_N - 1)
			stat->workers[i].y_end = h;
		else
			stat->workers[i].y_end = (h / RENDER_WORKER_N) * (i + 1);
		printf("%s: worker %d has been assigned on scanline %d - %d\n",
			EXEC_NAME, i, stat->workers[i].y_begin, stat->workers[i].y_end);
		i++;
	}
	return (ret);
}

int	init_workers(t_renderer *renderer, t_renderer_supervisor *stat)
{
	int	ret;
	int	i;
	int	h;

	renderer->stat = stat;
	ret = 0;
	ret |= pthread_mutex_init(&stat->m_finished, NULL);
	ret |= pthread_mutex_init(&stat->m_n_samples, NULL);
	ret |= pthread_mutex_init(&stat->m_milestone, NULL);
	settingman_display_size(SETTINGMAN_GET, NULL, &h, NULL);
	if (ret || set_worker_info(h, renderer, stat))
		return (ret | -1);
	i = 0;
	while (i < RENDER_WORKER_N)
	{
		ret |= pthread_create(&stat->ids[i], NULL,
				worker_routine, &stat->workers[i]);
		i++;
	}
	return (ret);
}

void	terminate_workers(t_renderer_supervisor *stat)
{
	int	i;

	set_render_finished(stat);
	i = 0;
	while (i < RENDER_WORKER_N)
	{
		pthread_join(stat->ids[i], NULL);
		i++;
	}
}
