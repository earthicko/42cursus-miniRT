/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:53:50 by dahkang           #+#    #+#             */
/*   Updated: 2023/03/07 14:53:51 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "material_bonus.h"
#include "geometry_bonus.h"
#include "hittable_internal_bonus.h"

static void	set_uv(t_hit_record *rec, const t_vec3 *outward_norm)
{
	double	theta;
	double	phi;

	theta = acos(-(outward_norm->i[1]));
	phi = atan2(-(outward_norm->i[2]), outward_norm->i[0]) + M_PI;
	rec->uv.i[0] = phi / (M_PI * 2);
	rec->uv.i[1] = theta / M_PI;
}

static void	set_coefficient(double coef[3],
							t_hittable_sphere *sphere,
							const t_ray *ray)
{
	t_vec3				oa;

	vec3_sub_vec3(&oa, &ray->orig, &sphere->center);
	coef[A] = vec3_dot_vec3(&ray->dir, &ray->dir);
	coef[B] = 2 * vec3_dot_vec3(&oa, &ray->dir);
	coef[C] = vec3_dot_vec3(&oa, &oa) - pow(sphere->radius, 2);
}

/*
	This function needs to solve equation system of sphere and straight line. 

	Sphere: (x_vec - O_point) * (x_vec - O_point) = radius^2
	   The trace of the vector x represents a sphere.
	   The given point O is the center of the sphere.
	Line: A_point + t * dir_vec
	   The given point A is origin of the line,
	   The vector dir is direction vector of line 
	By aligning the sphere and the straight line, 
	the following quadratic equation for 't' can be obtained. 
	at^2 + 2bt + c = 0, where
	a = dir * dir,
	2b = 2 * (dir * (A - O)),
	c = OA^2 - radius^2.
*/
t_bool	hit_sphere(t_hittable *hittable,
					const t_ray *ray,
					t_minmax t,
					t_hit_record *rec)
{
	t_hittable_sphere	*this;
	t_vec3				outward_norm;
	double				coef[3];
	double				root;

	if (!hittable->bbox.hit(&hittable->bbox, ray, &t))
		return (FALSE);
	this = (t_hittable_sphere *)hittable;
	set_coefficient(coef, this, ray);
	if (solver_quadratic_equation(t, coef, &root) == FALSE)
		return (FALSE);
	rec->t = root;
	ray_at(&rec->p, ray, rec->t);
	vec3_sub_vec3(&outward_norm, &rec->p, &this->center);
	vec3_mult_num_inplace(&outward_norm, 1 / this->radius);
	if (fabs(vec3_dot_vec3(&outward_norm, &ray->dir)) < DOUBLE_E)
		return (FALSE);
	hit_record_set_normal_and_face(rec, ray, &outward_norm);
	rec->material = this->material;
	set_uv(rec, &outward_norm);
	return (TRUE);
}

t_hittable	*hittable_sphere_create(
							t_point center,
							double radius,
							t_material *material)
{
	t_hittable_sphere	*sphere;
	t_point				min;
	t_point				max;
	t_vec3				rad;

	sphere = malloc(sizeof(t_hittable_sphere));
	if (!sphere)
		return (NULL);
	ft_memset(sphere, 0, sizeof(t_hittable_sphere));
	sphere->destroy = hittable_destroy;
	sphere->hit = hit_sphere;
	sphere->material = material;
	sphere->radius = radius;
	sphere->center = center;
	vec3_setval(&rad, radius, radius, radius);
	vec3_sub_vec3(&min, &center, &rad);
	vec3_add_vec3(&max, &center, &rad);
	bbox_init(&sphere->bbox, min, max);
	return ((t_hittable *)sphere);
}	
