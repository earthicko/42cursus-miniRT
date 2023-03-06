#include "geometry_bonus.h"
#include "ray_bonus.h"

void	ray_at(t_point *out, const t_ray *ray, double t)
{
	vec3_mult_num(out, &ray->dir, t);
	vec3_add_vec3_inplace(out, &ray->orig);
}
