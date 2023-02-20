#include "geometry.h"
#include "number.h"

void	vec3_rand(t_vec3 *out, double min, double max)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		out->i[i] = rand_double_range(min, max);
		i++;
	}
}

void	vec3_get_random_in_unit_sphere(t_vec3 *out)
{
	while (TRUE)
	{
		vec3_rand(out, -1, 1);
		if (vec3_get_len_sq(out) < 1.0)
			return ;
	}
}

void	vec3_get_random_unit(t_vec3 *out)
{
	vec3_get_random_in_unit_sphere(out);
	vec3_unitize(out);
}
