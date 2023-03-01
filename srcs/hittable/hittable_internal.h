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
t_bool	solver_quadratic_equation(t_minmax t, double coef[3], double *root);
t_bool	solver_equation_system_plane_and_line(const t_minmax t, \
												const t_hittable_plane *plane, \
												const t_ray *ray, \
												double *root);

/******* hit function for each object *******/

t_bool	hit_tube(t_hittable *hittable, \
					const t_ray *ray, \
					t_minmax t, \
					t_hit_record *rec);

t_bool	hit_disk(t_hittable *hittable, \
					const t_ray *ray, \
					t_minmax t, \
					t_hit_record *rec);

t_bool	hit_conical_hat(t_hittable *hittable, \
						const t_ray *ray, \
						t_minmax t, \
						t_hit_record *rec);

t_bool	hit_xy_rectangle(t_hittable *hittable, \
						const t_ray *ray, \
						t_minmax t, \
						t_hit_record *rec);

t_bool	hit_yz_rectangle(t_hittable *hittable, \
						const t_ray *ray, \
						t_minmax t, \
						t_hit_record *rec);

t_bool	hit_zx_rectangle(t_hittable *hittable, \
						const t_ray *ray, \
						t_minmax t, \
						t_hit_record *rec);

#endif
