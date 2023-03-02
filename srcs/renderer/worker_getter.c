#include <stdio.h>
#include "renderer_internal.h"

t_bool	is_render_finished(t_renderer_supervisor *stat)
{
	t_bool	finished;

	pthread_mutex_lock(&stat->m_finished);
	finished = stat->finished;
	pthread_mutex_unlock(&stat->m_finished);
	return (finished);
}

int	n_samples_main(t_renderer_supervisor *stat)
{
	int	n_samples;

	pthread_mutex_lock(&stat->m_n_samples);
	n_samples = stat->n_samples;
	pthread_mutex_unlock(&stat->m_n_samples);
	return (n_samples);
}

int	n_samples_worker(t_renderer_supervisor *stat, int i)
{
	int	n_samples;

	pthread_mutex_lock(&stat->workers[i].m_n_samples);
	n_samples = stat->workers[i].n_samples;
	pthread_mutex_unlock(&stat->workers[i].m_n_samples);
	return (n_samples);
}

int	milestone(t_renderer_supervisor *stat)
{
	int	milestone;

	pthread_mutex_lock(&stat->m_milestone);
	milestone = stat->milestone;
	pthread_mutex_unlock(&stat->m_milestone);
	return (milestone);
}

t_bool	all_workers_reach_milestone(t_renderer_supervisor *stat)
{
	int	i;
	int	current_milestone;

	current_milestone = milestone(stat);
	i = 0;
	while (i < RENDER_WORKER_N)
	{
		if (n_samples_worker(stat, i) < current_milestone)
			return (FALSE);
		i++;
	}
	printf("All workers has reached milestone %d\n", current_milestone);
	return (TRUE);
}
