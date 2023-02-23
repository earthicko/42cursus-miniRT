#ifndef RAY_H
# define RAY_H

# include "geometry.h"

typedef t_point	(*t_at)(t_ray *this, double t);

typedef struct s_ray
{
	t_point	orig;
	t_vec3	dir;
	t_at	at;
}	t_ray;

#endif
