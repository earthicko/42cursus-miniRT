#include "hittable_bonus.h"
#include "ray_bonus.h"

void	hit_record_set_normal_and_face(
			t_hit_record *rec, const t_ray *ray, const t_vec3 *normal)
{
	if (vec3_dot_vec3(&ray->dir, normal) < 0)
	{
		rec->is_front = TRUE;
		rec->normal = *normal;
	}
	else
	{
		rec->is_front = FALSE;
		vec3_mult_num(&rec->normal, normal, -1);
	}
}
