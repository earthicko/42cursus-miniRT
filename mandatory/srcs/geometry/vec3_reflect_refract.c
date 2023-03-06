#include <math.h>
#include "geometry.h"

/*
	out = in - 2 * (in . normal) * normal
*/
void	vec3_reflect(t_vec3 *out, const t_vec3 *in, const t_vec3 *normal)
{
	double	dot;
	int		i;

	dot = vec3_dot_vec3(in, normal);
	i = 0;
	while (i < 3)
	{
		out->i[i] = in->i[i] - 2 * dot * normal->i[i];
		i++;
	}
}

/*
	out = perpendicular component + parallel component
	perpendicular = ratio * (in + cos(theta) * normal)
	parallel = -(|1 - len(perpendicular) ^ 2|) ^ 1/2 * normal
*/
void	vec3_refract(t_vec3 *out, const t_vec3 *in, const t_vec3 *n, double r)
{
	double	costheta;
	t_vec3	in_inv;
	t_vec3	component_perp;
	t_vec3	component_paral;
	int		i;

	vec3_mult_num(&in_inv, in, -1);
	costheta = fmin(vec3_dot_vec3(&in_inv, n), 1.0);
	i = 0;
	while (i < 3)
	{
		component_perp.i[i] = r * (in->i[i] + costheta * n->i[i]);
		i++;
	}
	vec3_mult_num(&component_paral,
		n, -sqrt(fabs(1.0 - vec3_get_len_sq(&component_perp))));
	vec3_add_vec3(out, &component_perp, &component_paral);
}
