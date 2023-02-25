#include "geometry.h"
#include "ray.h"

void	ray_at(t_point *out, const t_ray *ray, double t)
{
	vec3_mult_num(out, &ray->dir, t);
	vec3_add_vec3_inplace(out, &ray->orig);
}

void	ray_multiply_m44(t_ray *out, const t_ray *ray, const t_mtx44 *m)
{
	vec3_multiply_m44(&out->orig, &ray->orig, m);
	vec3_multiply_m44(&out->dir, &ray->dir, m);
}

void	ray_multiply_m44_inplace(t_ray *target, const t_mtx44 *m)
{
	vec3_multiply_m44_inplace(&target->orig, m);
	vec3_multiply_m44_inplace(&target->dir, m);
}
