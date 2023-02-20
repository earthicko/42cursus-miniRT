#include "libft.h"
#include "geometry.h"

void	vec3_mult_num(t_vec3 *out, t_vec3 *a, double b)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		out->i[i] = a->i[i] * b;
		i++;
	}
}

void	vec3_mult_num_inplace(t_vec3 *a, double b)
{
	t_vec3	temp;

	vec3_mult_num(&temp, a, b);
	ft_memcpy(a, &temp, sizeof(t_vec3));
}
