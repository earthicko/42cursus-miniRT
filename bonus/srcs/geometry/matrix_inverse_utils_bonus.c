#include "geometry_bonus.h"
#include "number_bonus.h"

static double	get_pivotsize(int *pivot, t_mtx44 *copy, int i)
{
	int		j;
	double	tmp;
	double	pivotsize;

	pivotsize = copy->i[i][i];
	if (pivotsize < 0)
		pivotsize = -pivotsize;
	j = i + 1;
	while (j < 4)
	{
		tmp = copy->i[j][i];
		if (tmp < 0)
			tmp = -tmp;
		if (tmp > pivotsize)
		{
			*pivot = j;
			pivotsize = tmp;
		}
		j++;
	}
	return (pivotsize);
}

static int	choose_pivot(t_mtx44 *copy, t_mtx44 *out, int i)
{
	int		j;
	int		pivot;
	double	pivotsize;

	pivot = i;
	pivotsize = get_pivotsize(&pivot, copy, i);
	if (pivotsize == 0)
		return (-1);
	if (pivot != i)
	{
		j = 0;
		while (j < 4)
		{
			swap_double(&copy->i[i][j], &copy->i[pivot][j]);
			swap_double(&out->i[i][j], &out->i[pivot][j]);
			j++;
		}
	}
	return (0);
}

static void	eliminate_below_diagonal(t_mtx44 *copy, t_mtx44 *out, int i)
{
	int		j;
	int		k;
	double	tmp;

	j = i + 1;
	while (j < 4)
	{
		tmp = copy->i[j][i] / copy->i[i][i];
		k = 0;
		while (k < 4)
		{
			copy->i[j][k] -= tmp * copy->i[i][k];
			out->i[j][k] -= tmp * out->i[i][k];
			k++;
		}
		copy->i[j][i] = 0.0;
		j++;
	}
}

int	forward_elimination(t_mtx44 *copy, t_mtx44 *out)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (choose_pivot(copy, out, i))
			return (-1);
		eliminate_below_diagonal(copy, out, i);
		i++;
	}
	return (0);
}
