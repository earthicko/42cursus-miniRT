#include <math.h>
#include "hittable_internal.h"

t_bool	solve_quadratic_equation(t_minmax t, double coef[3], double *root)
{
	double	dscrm;
	double	sqrt_dscrm;

	dscrm = pow(coef[B], 2) - 4 * coef[A] * coef[C];
	if (dscrm < 0)
		return (FALSE);
	sqrt_dscrm = sqrt(dscrm);
	*root = (-coef[B] - sqrt_dscrm) / 2 * coef[A];
	if (*root < t.min || *root > t.max)
	{
		*root = (-coef[B] + sqrt_dscrm) / 2 * coef[A];
		if (*root < t.min || *root > t.max)
			return (FALSE);
	}
	return (TRUE);
}

// TODO: ray가 평면이랑 평행하거나, 거의 평행할 때 예외처리 (0으로 나누게 됨)
// TODO: 교점이 무수히 많을 때 (?)

// 상식적으로 생각했을 때, 표면을 스치듯 지나가는 광선은 표면 밝기에 영향력이 거의 0
// 따라서 위 두가지 경우 그냥 hit하지 않는다고 판단해도 무방할듯
// t_bool	solve_equation_system_plane_and_line(t_minmax t, \
// 											t_plane *pl, \
// 											t_ray *ray, \
// 											double *root)
// {
// 	const double	norm_dot_dir = vec3_dot_vec3(&pl->norm, &ray->dir);
// 	double			coef[4];

// 	// if (norm_dot_dir == near_zero)
// 	// {
// 	// 	if (ray->orig is on pl)
// 	// 		//직선이 평면에 포함, 무수히 많은 교점
// 	// 	else
// 	// 		//평행, 교점 0개
// 	// }
// 	coef[D] = -vec3_dot_vec3(&pl->norm, &pl->point)
// 	*root = (-vec3_dot_vec3(&pl->norm, &ray->orig) - coef[D]) / norm_dot_dir;
// 	return (TRUE);
// }
