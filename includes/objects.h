#ifndef OBJECTS_H
# define OBJECTS_H

# include "geometry.h"
# include "hittable.h"

typedef struct s_sphere
{
	t_hit		hit;
	double		radius;
	t_point		center;	
	t_material	*material;
	t_color		color;
}	t_sphere;

typedef struct s_plane
{
	t_hit		hit;
	t_point		point;
	t_vec3		norm;
	t_material	*material;
	t_color		color;
}	t_plane;

// TODO: 오브젝트를 옆면과, 뚜껑 2개로 나누기
typedef struct s_cylinder
{
	t_hit		hit;
	t_point		cen_of_base;
	t_vec3		axis;
	t_material	*material;
	t_color		color;
}	t_cylinder;

#endif
