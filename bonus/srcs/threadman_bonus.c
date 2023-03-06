/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadman_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "settingman_bonus.h"
#include "threadman_bonus.h"

int	threadman(int mode, int idx, void *(*routine)(void *), void *arg)
{
	static pthread_t	ids[RENDER_WORKER_N];
	int					i;

	if (mode == CREATE)
		return (pthread_create(&ids[idx], NULL, routine, arg));
	else if (mode == JOIN)
	{
		i = -1;
		while (++i < RENDER_WORKER_N)
		{
			pthread_join(ids[i], NULL);
			ids[i] = 0;
		}
	}
	else if (mode == GETID)
	{
		i = -1;
		while (++i < RENDER_WORKER_N)
		{
			if (pthread_equal(ids[i], pthread_self()))
				return (i);
		}
		return (-1);
	}
	return (0);
}
