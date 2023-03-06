#ifndef RAY_H
# define RAY_H

# include "geometry.h"

typedef struct s_ray
{
	t_point	orig;
	t_vec3	dir;
}	t_ray;

void	ray_at(t_point *out, const t_ray *ray, double t);

#endif
