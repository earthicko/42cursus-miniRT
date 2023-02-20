#include "geometry.h"

void	m44_init_zero(t_matrix44 *m)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		m->i[i / 4][i % 4] = 0;
		i++;
	}
}

void	m44_init_identity(t_matrix44 *m)
{
	int	i;

	m44_init_zero(m);
	i = 0;
	while (i < 4)
	{
		m->i[i][i] = 1;
		i++;
	}
}
