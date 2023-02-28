#include <math.h>
#include "libft.h"
#include "material.h"
#include "geometry.h"
#include "hittable_internal.h"

static t_bool	ray_and_outward_norm_perpendicular(const t_ray *ray,
													t_vec3 *norm)
{
	if (fabs(vec3_dot_vec3(&ray->dir, norm)) < DOUBLE_E)
		return (TRUE);
	return (FALSE);
}

/*
	The point C is center of the disk. (Yes, it's plane.point)
	If PC > r, then root we got is out of. 
*/
static t_bool	root_is_out_of_range(t_hittable_disk *disk, t_hit_record *rec)
{
	if (dist_sq(&rec->p, &disk->plane.point) > pow(disk->radius, 2))
		return (TRUE);
	return (FALSE);
}

// TODO: hit 함수들 static으로 수정해볼 것
/*
	This function needs to solve equation system of plane and straight line. 
	The additional thing to do is to make sure,
	that the solution fits the given range. (Because it's circle!)
	See the comment of the solver_equation_system_plane_and_line for details.
*/
t_bool	hit_disk(t_hittable *hittable,
					const t_ray *ray,
					t_minmax t,
					t_hit_record *rec)
{
	t_hittable_disk	*this;
	t_vec3			outward_norm;
	double			root;

	this = (t_hittable_disk *)hittable;
	if (ray_and_outward_norm_perpendicular(ray, &this->plane.norm))
		return (FALSE);
	if (solver_equation_system_plane_and_line(t, &this->plane, ray, &root)
		== FALSE)
		return (FALSE);
	rec->t = root;
	ray_at(&rec->p, ray, rec->t);
	if (root_is_out_of_range(this, rec))
		return (FALSE);
	rec->material = this->material;
	outward_norm = this->plane.norm;
	hit_record_set_normal_and_face(rec, ray, &outward_norm);
	return (TRUE);
}
