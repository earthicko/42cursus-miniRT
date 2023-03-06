#ifndef THREADMAN_H
# define THREADMAN_H

enum e_threadmanmode
{
	CREATE = 0,
	JOIN,
	GETID
};

int	threadman(int mode, int idx, void *(*routine)(void *), void *arg);

#endif
