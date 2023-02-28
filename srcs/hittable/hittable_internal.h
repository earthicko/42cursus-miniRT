#ifndef HITTABLE_INTERNAL_H
# define HITTABLE_INTERNAL_H

# include "hittable.h"

enum	e_coefficient
{
	A = 0,
	B,
	C,
};

/******* math_utils *******/

t_bool	val_is_near_zero(double val);
double	dist_sq(t_point *a, t_point *b);
t_bool	solve_quadratic_equation(t_minmax t, double coef[3], double *root);
t_bool	solve_equation_system_plane_and_line(const t_minmax t, \
												const t_hittable_plane *plane, \
												const t_ray *ray, \
												double *root);


/******* Set cylinder's elements *******/

void	set_tube_of_cylinder(t_hittable_tube *tube, \
								t_cylinder_info *cylinder_info, \
								t_material *material);

void	set_disk_of_cylinder(t_hittable_disk *disk, \
								t_cylinder_info *cylinder_info, \
								t_material *material, \
								int disk_type);


/******* Set cones's elements *******/

void	set_disk_of_cone(t_hittable_disk *disk, \
							t_cone_info *cone_info, \
							t_material *material);

void	set_conical_hat_of_cylinder(t_hittable_conical_hat *conical_hat, \
									t_cone_info *cone_info, \
									t_material *material);
#endif
