#ifndef THREADMAN_BONUS_H
# define THREADMAN_BONUS_H

enum e_threadmanmode
{
	CREATE = 0,
	JOIN,
	GETID
};

int	threadman(int mode, int idx, void *(*routine)(void *), void *arg);

#endif
