#include <math.h>
#include "number.h"
#include "geometry.h"
#include "hittable_internal.h"

t_bool	val_is_near_zero(double val)
{
	if (fabs(val) < DOUBLE_E)
		return (TRUE);
	return (FALSE);
}

double	dist_sq(t_point *a, t_point *b)
{
	t_vec3	b_to_a;

	vec3_sub_vec3(&b_to_a, a, b);
	return (vec3_get_len_sq(&b_to_a));
}

/*  This function solves ax^2 + bx + c = 0 equation.
	Each coef element refers to a, b, and c respectively.
 	If this function finds a solution that fits the range of t_minmax, 
 	it stores the result in root parameter and returns true. 
*/
t_bool	solve_quadratic_equation(t_minmax t, double coef[3], double *root)
{
	double	dscrm;
	double	sqrt_dscrm;

	dscrm = pow(coef[B], 2) - 4 * coef[A] * coef[C];
	if (dscrm < 0)
		return (FALSE);
	sqrt_dscrm = sqrt(dscrm);
	*root = (-coef[B] - sqrt_dscrm) / (2 * coef[A]);
	if (*root < t.min || *root > t.max)
	{
		*root = (-coef[B] + sqrt_dscrm) / (2 * coef[A]);
		if (*root < t.min || *root > t.max)
			return (FALSE);
	}
	return (TRUE);
}

// TODO: ray가 평면이랑 평행하거나, 거의 평행할 때 예외처리 (0으로 나누게 됨)
// TODO: 교점이 무수히 많을 때 (?)
// 잠정적 결론:
// 상식적으로 생각했을 때, 표면을 스치듯 지나가는 광선은 표면 밝기에 영향력이 거의 없다.
// 따라서 위 두가지 경우 그냥 hit하지 않는다고 판단해도 무방할듯

/*
	This function solves equation system of plane and straight line.
	 Plane: n_vec * (x_vec - P_point), 
	    Vector n is normal vector of plane, 
	    The given point P is a point on the plane,
	    The trace of the vector x represents a plane.
	 Line: A_point + t * dir_vec
	    The given point A is origin of the line,
	    The vector u is direction vector of the line 
	Solution: t = (P - A) * n_vec / n_vec * dir_vec
*/
t_bool	solve_equation_system_plane_and_line(const t_minmax t,
											const t_hittable_plane *plane,
											const t_ray *ray,
											double *root)
{
	const double	norm_dot_dir = vec3_dot_vec3(&plane->norm, &ray->dir);
	t_vec3			ap;

	(void)t;
	if (val_is_near_zero(norm_dot_dir))
		return (FALSE);
	vec3_sub_vec3(&ap, &plane->point, &ray->orig);
	*root = vec3_dot_vec3(&ap, &plane->norm) / norm_dot_dir;
	if (*root < t.min || *root > t.max)
		return (FALSE);
	return (TRUE);
}
