#include "libft.h"
#include "geometry.h"

double	vec3_dot_vec3(const t_vec3 *a, const t_vec3 *b)
{
	double	out;
	int		i;

	out = 0;
	i = 0;
	while (i < 3)
	{
		out += a->i[i] * b->i[i];
		i++;
	}
	return (out);
}
