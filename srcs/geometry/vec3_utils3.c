#include <math.h>
#include "geometry.h"
#include "number.h"

void	vec3_rand_ts(t_vec3 *out, double min, double max)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		out->i[i] = rand_double_range_ts(min, max);
		i++;
	}
}

void	vec3_get_random_in_unit_sphere_ts(t_vec3 *out)
{
	while (TRUE)
	{
		vec3_rand_ts(out, -1, 1);
		if (vec3_get_len_sq(out) < 1.0)
			return ;
	}
}

void	vec3_get_random_unit_ts(t_vec3 *out)
{
	vec3_get_random_in_unit_sphere_ts(out);
	vec3_unitize(out);
}
