#include "libft.h"
#include "geometry_bonus.h"

void	vec3_add_vec3(t_vec3 *out, const t_vec3 *a, const t_vec3 *b)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		out->i[i] = a->i[i] + b->i[i];
		i++;
	}
}

void	vec3_add_vec3_inplace(t_vec3 *target, const t_vec3 *b)
{
	t_vec3	temp;

	vec3_add_vec3(&temp, target, b);
	ft_memcpy(target, &temp, sizeof(t_vec3));
}
