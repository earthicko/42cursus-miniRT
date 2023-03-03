#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "material.h"
#include "geometry.h"
#include "hittable_internal.h"

t_bool	hit_box(t_hittable *hittable,
					const t_ray *ray,
					t_minmax t,
					t_hit_record *rec)
{
	(void)hittable;
	(void)ray;
	(void)t;
	(void)rec;
	ft_printf("Unimplemented stub of %s\n", __func__);
	return (FALSE);
}

t_hittable	*hittable_box_create(t_box_info *info)
{
	t_hittable_box	*box;

	box = malloc(sizeof(t_hittable_box));
	if (!box)
		return (NULL);
	ft_memset(box, 0, sizeof(t_hittable_box));
	box->hit = hit_box;
	(void)info;
	ft_printf("Unimplemented stub of %s\n", __func__);
	return ((t_hittable *)box);
}	
