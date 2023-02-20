#ifndef OBJECTS_H
# define OBJECTS_H

# include "geometry.h"

// TODO: 자료형 타입 맞출 것
typedef int	t_material;

typedef struct s_sphere
{
	double		radius;
	t_point3	center;	
	t_material	*material;
	t_color		color;
}	t_sphere;

typedef struct s_plane
{
	t_point3	point;
	t_vec3		norm;
	t_material	*material;
	t_color		color;
}	t_plane;

typedef struct s_cylinder
{
	t_point3	cen_of_base;
	t_vec3		norm;
	t_material	*material;
	t_color		color;
}	t_cylinder;

#endif
