#include <stdlib.h>
#include "libft.h"
#include "geometry.h"
#include "number.h"
#include "material.h"
#include "hittable_internal.h"

/*
	For details, see hit functions for each elements.
*/
t_bool	hit_cone(t_hittable *hittable,
					const t_ray *ray,
					t_minmax t,
					t_hit_record *rec)
{
	t_hittable_cone	*this;

	this = (t_hittable_cone *)hittable;
	if (this->conical_hat.hit((t_hittable *)&this->conical_hat, ray, t, rec))
		t.max = rec->t;
	if (this->disk.hit((t_hittable *)&this->disk, ray, t, rec))
		t.max = rec->t;
	if (val_is_near_zero(t.max - DOUBLE_INF))
		return (FALSE);
	return (TRUE);
}

t_hittable	*hittable_cone_create(t_cone_info *cone_info,
									t_material *material)
{
	t_hittable_cone	*cone;

	cone = malloc(sizeof(t_hittable_cone));
	if (!cone)
		return (NULL);
	ft_memset(cone, 0, sizeof(t_hittable_cone));
	cone->hit = hit_cone;
	cone->material = material;
	set_disk_of_cone(&cone->disk, cone_info, material);
	set_conical_hat_of_cone(&cone->conical_hat, cone_info, material);
	return ((t_hittable *)cone);
}