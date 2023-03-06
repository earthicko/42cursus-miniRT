/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker_getter_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "renderer_internal_bonus.h"

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
	int	n_samples;

	current_milestone = milestone(stat);
	i = 0;
	while (i < RENDER_WORKER_N)
	{
		n_samples = n_samples_worker(stat, i);
		renderer_render_showstat_multithread(n_samples, i);
		if (n_samples < current_milestone)
			return (FALSE);
		i++;
	}
	return (TRUE);
}
