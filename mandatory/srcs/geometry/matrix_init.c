#include "geometry.h"

void	m44_init_zero(t_mtx44 *target)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		target->i[i / 4][i % 4] = 0;
		i++;
	}
}

void	m44_init_identity(t_mtx44 *target)
{
	int	i;

	m44_init_zero(target);
	i = 0;
	while (i < 4)
	{
		target->i[i][i] = 1;
		i++;
	}
}
