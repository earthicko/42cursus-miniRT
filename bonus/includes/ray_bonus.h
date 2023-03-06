#ifndef RAY_BONUS_H
# define RAY_BONUS_H

# include "geometry_bonus.h"

typedef struct s_ray
{
	t_point	orig;
	t_vec3	dir;
}	t_ray;

void	ray_at(t_point *out, const t_ray *ray, double t);

#endif
