#include "libft.h"
#include "geometry.h"

void	parse_vector(t_vec3 *out, const void **token_start)
{
	out->i[0] = ft_atof(token_start[0]);
	out->i[1] = ft_atof(token_start[2]);
	out->i[2] = ft_atof(token_start[4]);
}
