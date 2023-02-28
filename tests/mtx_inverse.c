#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "geometry.h"
#include "print.h"

static void	fill_mtx(int nmtx, t_mtx44 *mtx)
{
	int	n;
	int	i;
	int	j;

	n = 0;
	while (n < nmtx)
	{
		i = 0;
		while (i < 4)
		{
			j = 0;
			while (j < 4)
			{
				mtx[n].i[i][j] = (double)rand() / RAND_MAX;
				j++;
			}
			i++;
		}
		n++;
	}
}

int	main(void)
{
	int		i;
	t_mtx44	mat[2];
	t_mtx44	inv[2];
	t_mtx44	mult[2];

	srand(time(NULL));
	fill_mtx(2, mat);
	i = 0;
	while (i < 2)
	{
		m44_get_inverse(&inv[i], &mat[i]);
		m44_multiply_m44(&mult[i], &mat[i], &inv[i]);
		printf("original: \n");
		print_mtx44(&mat[i]);
		printf("inverse: \n");
		print_mtx44(&inv[i]);
		printf("mult: \n");
		print_mtx44(&mult[i]);
		i++;
	}
	return (0);
}
