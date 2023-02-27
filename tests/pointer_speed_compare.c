#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "geometry.h"

t_vec3	vec3_add_vec3_new(const t_vec3 *a, const t_vec3 *b)
{
	t_vec3	result;
	int		i;

	i = 0;
	while (i < 3)
	{
		result.i[i] = a->i[i] + b->i[i];
		i++;
	}
	return (result);
}

void	fill_vec3(t_vec3 *a, t_vec3 *b, int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < 3)
		{
			a[i].i[j] = (double)rand() / RAND_MAX;
			b[i].i[j] = (double)rand() / RAND_MAX;
			j++;
		}
		i++;
	}
}

double	test_original(t_vec3 *a, t_vec3 *b, int n)
{
	int		i;
	clock_t	start;
	clock_t	end;
	t_vec3	*c;

	start = clock();
	c = malloc(n * sizeof(t_vec3));
	i = 0;
	while (i < n)
	{
		vec3_add_vec3(&c[i], &a[i], &b[i]);
		i++;
	}
	end = clock();
	free(c);
	return ((double)(end - start) / CLOCKS_PER_SEC);
}

double	test_new(t_vec3 *a, t_vec3 *b, int n)
{
	int		i;
	clock_t	start;
	clock_t	end;
	t_vec3	*c;

	start = clock();
	c = malloc(n * sizeof(t_vec3));
	i = 0;
	while (i < n)
	{
		c[i] = vec3_add_vec3_new(&a[i], &b[i]);
		i++;
	}
	end = clock();
	free(c);
	return ((double)(end - start) / CLOCKS_PER_SEC);
}

int	main(void)
{
	int		n;
	t_vec3	*a;
	t_vec3	*b;

	n = 1000000;
	srand(time(NULL));
	a = malloc(n * sizeof(t_vec3));
	b = malloc(n * sizeof(t_vec3));
	fill_vec3(a, b, n);
	printf("fill finished\n");
	printf("Original function took %f seconds.\n", test_original(a, b, n));
	printf("Modified function took %f seconds.\n", test_new(a, b, n));
	return (0);
}
