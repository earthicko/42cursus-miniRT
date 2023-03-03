#include <pthread.h>
#include "settingman.h"
#include "threadman.h"

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
