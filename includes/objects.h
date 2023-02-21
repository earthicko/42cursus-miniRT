#ifndef OBJECTS_H
# define OBJECTS_H

# include "geometry.h"
# include "hittable.h"

typedef struct s_sphere
{
	t_hit			hit;
	t_bounding_box	bounding_box;
	double			radius;
	t_point			center;	
	t_material		*material;
	t_color			color;
}	t_sphere;

typedef struct s_plane
{
	t_hit			hit;
	t_bounding_box	bounding_box;
	t_point			point;
	t_vec3			norm;
	t_material		*material;
	t_color			color;
}	t_plane;

typedef struct s_cylinder
{
	t_hit			hit;
	t_bounding_box	bounding_box;
	t_point			cen_of_base;
	t_vec3			axis;
	t_material		*material;
	t_color			color;
}	t_cylinder;

typedef struct s_side_of_cy
{
	t_hit			hit;
	t_bounding_box	bounding_box;
	t_point			cen_of_base;
	t_vec3			axis;
	t_material		*material;
	t_color			color;
}	t_side_of_cy;

typedef struct s_base_of_cy
{
	t_hit			hit;
	t_bounding_box	bounding_box;
	t_point			cen_of_base;
	t_material		*material;
	t_color			color;
}	t_base_of_cy;

#endif
