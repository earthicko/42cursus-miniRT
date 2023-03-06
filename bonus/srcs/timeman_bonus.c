#include <stdio.h>
#include <time.h>

// TODO: remove timeman before submission
void	timeman(int mode)
{
	static clock_t	t;
	static clock_t	t_now;
	double			t_sec;

	if (mode == 0)
	{
		t = clock();
		printf("clock set at %lu\n", t);
	}
	else
	{
		t_now = clock() - t;
		t_sec = ((double)t_now) / CLOCKS_PER_SEC;
		printf("lap clock %lu (%.5f sec)\n", t_now, t_sec);
	}
}
