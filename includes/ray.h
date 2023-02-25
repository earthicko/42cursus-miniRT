#ifndef RAY_H
# define RAY_H

# include "geometry.h"

typedef struct s_ray
{
	t_point	orig;
	t_vec3	dir;
}	t_ray;

void	ray_at(t_point *out, const t_ray *ray, double t);
void	ray_multiply_m44(t_ray *out, const t_ray *ray, const t_mtx44 *m);
void	ray_multiply_m44_inplace(t_ray *target, const t_mtx44 *m);

#endif
