#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "material.h"
#include "geometry.h"
#include "number.h"
#include "hittable_internal.h"

static t_bool	ray_and_outward_norm_perpendicular(const t_ray *ray,
													t_vec3 *norm)
{
	if (fabs(vec3_dot_vec3(&ray->dir, norm)) < DOUBLE_E)
		return (TRUE);
	return (FALSE);
}

/*
	This function needs to solve equation system of plane and straight line. 
	See the comment of the solver_equation_system_plane_and_line for details.
*/
t_bool	hit_plane(t_hittable *hittable,
					const t_ray *ray,
					t_minmax t,
					t_hit_record *rec)
{
	t_hittable_plane	*this;
	t_vec3				outward_norm;
	double				root;

	this = (t_hittable_plane *)hittable;
	if (ray_and_outward_norm_perpendicular(ray, &this->norm))
		return (FALSE);
	if (solver_equation_system_plane_and_line(t, this, ray, &root) == FALSE)
		return (FALSE);
	rec->t = root;
	ray_at(&rec->p, ray, rec->t);
	outward_norm = this->norm;
	hit_record_set_normal_and_face(rec, ray, &outward_norm);
	rec->material = this->material;
	vec2_setval(&rec->uv, 0, 0);
	return (TRUE);
}

t_hittable	*hittable_plane_create(t_point point,
							t_vec3 norm,
							t_material *material)
{
	t_hittable_plane	*plane;

	plane = malloc(sizeof(t_hittable_plane));
	if (!plane)
		return (NULL);
	ft_memset(plane, 0, sizeof(t_hittable_plane));
	plane->destroy = hittable_destroy;
	plane->hit = hit_plane;
	plane->material = material;
	plane->point = point;
	plane->norm = norm;
	return ((t_hittable *)plane);
}
