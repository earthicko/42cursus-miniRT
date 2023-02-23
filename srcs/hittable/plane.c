#include <stdlib.h>
#include "libft.h"
#include "hittable_internal.h"
#include "material.h"
#include "geometry.h"
#include "objects.h"

// TODO: outward_norm 필요성, 필요하긴 할듯. ray color 함수 잘 보고 판단
t_bool	hit_plane(t_hittable *hittable, \
					t_ray *ray, \
					t_pair t, \
					t_hit_record *rec)
{
	t_plane	*this;
	t_vec3	outward_norm;
	double	root;

	this = (t_plane *)hittable;
	if (solve_equation_system_plane_and_line(t, this, ray, &root) == FALSE)
		return (FALSE);
	rec->t = root;
	rec->p = ray->at(ray, rec.t);
	outward_norm = this->norm;
	hit_record_set_normal_and_face(rec, ray, outward_norm);
	rec->material = this->material;
	return (TRUE);
}