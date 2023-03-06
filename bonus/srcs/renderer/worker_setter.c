#include <stdio.h>
#include "renderer_internal.h"

void	set_render_finished(t_renderer_supervisor *stat)
{
	pthread_mutex_lock(&stat->m_finished);
	stat->finished = TRUE;
	pthread_mutex_unlock(&stat->m_finished);
	printf("Render finished.\n");
}

void	set_milestone(t_renderer_supervisor *stat, int milestone)
{
	pthread_mutex_lock(&stat->m_milestone);
	stat->milestone = milestone;
	pthread_mutex_unlock(&stat->m_milestone);
}

void	set_n_samples_main(t_renderer_supervisor *stat, int n_samples)
{
	pthread_mutex_lock(&stat->m_n_samples);
	stat->n_samples = n_samples;
	pthread_mutex_unlock(&stat->m_n_samples);
}

void	set_n_samples_worker(t_renderer_supervisor *stat, int i, int n_samples)
{
	pthread_mutex_lock(&stat->workers[i].m_n_samples);
	stat->workers[i].n_samples = n_samples;
	pthread_mutex_unlock(&stat->workers[i].m_n_samples);
}
