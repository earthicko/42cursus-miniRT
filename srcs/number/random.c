#include "libft.h"

double	rand_double(void)
{
	return (ft_rand() / (FT_RAND_MAX + 1.0));
}

double	rand_double_range(double min, double max)
{
	return (min + (max - min) * rand_double());
}

int	rand_range(int min, int max)
{
	return (min + ft_rand() % (max - min));
}
