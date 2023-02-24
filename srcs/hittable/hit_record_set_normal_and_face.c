#include "hittable.h"
#include "ray.h"

void	hit_record_set_normal_and_face(
			t_hit_record *hit, t_ray *ray, t_vec3 *normal)
{
	if (vec3_dot_vec3(&ray->dir, normal) < 0)
	{
		hit->is_front = TRUE;
		hit->normal = *normal;
	}
	else
	{
		hit->is_front = FALSE;
		vec3_mult_num(&hit->normal, normal, -1);
	}
}
