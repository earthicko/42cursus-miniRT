#ifndef HITTABLE_INTERNAL_H
# define HITTABLE_INTERNAL_H

# include "hittable.h"

enum	e_coefficient
{
	A = 0,
	B,
	C,
};

t_bool	val_is_near_zero(double val);
double	dist_sq(t_point *a, t_point *b);
t_bool	solve_quadratic_equation(t_minmax t, double coef[3], double *root);
t_bool	solve_equation_system_plane_and_line(
			t_minmax t,
			t_hittable_plane *plane,
			t_ray *ray,
			double *root);

void	set_tube_of_cylinder(
			t_hittable_tube *tube,
			t_cylinder_info *cylinder_info,
			t_material *material);

void	set_disk_of_cylinder(
			t_hittable_disk *disk,
			t_cylinder_info *cylinder_info,
			t_material *material,
			int disk_type);

#endif
