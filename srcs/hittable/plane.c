#include <stdlib.h>
#include "libft.h"
#include "material.h"
#include "geometry.h"
#include "hittable_internal.h"

// TODO: outward_norm 필요성, 필요하긴 할듯. one weekend ray_color 함수읽고 판단할 것
t_bool	hit_plane(t_hittable *hittable,
					t_ray *ray,
					t_minmax t,
					t_hit_record *rec)
{
	t_hittable_plane	*this;
	t_vec3				outward_norm;
	double				root;

	this = (t_hittable_plane *)hittable;
	if (solve_equation_system_plane_and_line(t, this, ray, &root) == FALSE)
		return (FALSE);
	rec->t = root;
	ray_at(&rec->p, ray, rec->t);
	outward_norm = this->norm;
	hit_record_set_normal_and_face(rec, ray, &outward_norm);
	rec->material = this->material;
	return (TRUE);
}

t_hittable_plane	*plane_create(t_point point,
									t_vec3 norm,
									t_material *material)
{
	t_hittable_plane	*plane;

	plane = malloc(sizeof(t_hittable_plane));
	if (!plane)
		return (NULL);
	ft_memset(plane, 0, sizeof(t_hittable_plane));
	plane->hit = hit_plane;
	plane->material = material;
	plane->point = point;
	plane->norm = norm;
	return (plane);
}
