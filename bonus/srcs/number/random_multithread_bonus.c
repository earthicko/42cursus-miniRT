/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_multithread_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "settingman_bonus.h"
#include "threadman_bonus.h"

int	ft_rand_ts(void)
{
	static int				init[RENDER_WORKER_N + 1];
	static unsigned long	next[RENDER_WORKER_N + 1];
	int						tid;

	tid = threadman(GETID, 0, 0, 0);
	if (tid == -1)
		tid = RENDER_WORKER_N;
	if (init[tid] == 0)
	{
		next[tid] = 1;
		init[tid] = 1;
	}
	next[tid] = next[tid] * 1103515245 + 12345;
	return ((int)((next[tid] / 65536) % FT_RAND_MAX));
}

double	rand_double_ts(void)
{
	return (ft_rand_ts() / (FT_RAND_MAX + 1.0));
}

double	rand_double_range_ts(double min, double max)
{
	return (min + (max - min) * rand_double_ts());
}

int	rand_range_ts(int min, int max)
{
	return (min + ft_rand_ts() % (max - min));
}
