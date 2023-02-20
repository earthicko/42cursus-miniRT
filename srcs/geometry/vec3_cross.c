#include "libft.h"
#include "geometry.h"

void	vec3_cross_vec3(t_vec3 *out, t_vec3 *a, t_vec3 *b)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		out->i[i] = a->i[(i + 1) % 3] * b->i[(i + 2) % 3]
			- a->i[(i + 2) % 3] * b->i[(i + 1) % 3];
		i++;
	}
}
