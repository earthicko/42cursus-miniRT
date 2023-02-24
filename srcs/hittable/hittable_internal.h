#ifndef HITTABLE_INTERNAL_H
# define HITTABLE_INTERNAL_H

# include "libft_def.h"
# include "hittable.h"

enum	e_coefficient
{
	A = 0,
	B,
	C,
	D
};

t_bool	solve_quadratic_equation(t_minmax t, double coef[3], double *root);

#endif