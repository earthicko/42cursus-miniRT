#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "geometry.h"
#include "number.h"
#include "material.h"
#include "hittable_internal.h"

/*
static int	cylinder_destructor(t_hittable_cylinder *cylinder, int err_code)
{
	free(cylinder->disk[0]);
	free(cylinder->disk[1]);
	free(cylinder->tube);
	free(cylinder);
	return (err_code);
}
*/

/*
static int	init_cylinder_and_elements(t_hittable_cylinder **cylinder,
										t_cylinder_info *cylinder_info,
										t_material *material)
{
	*cylinder = malloc(sizeof(t_hittable_cylinder));
	if (!*cylinder)
		return (CODE_ERROR_MALLOC);
	ft_memset(*cylinder, 0, sizeof(t_hittable_cylinder));
	cylinder->tube = malloc(sizeof(t_hittable_tube));
	cylinder->disk[0] = malloc(sizeof(t_hittable_disk));
	cylinder->disk[1] = malloc(sizeof(t_hittable_disk));
	if (!cylinder->tube || !cylinder->disk[0] || !cylinder->disk[1])
		return (cylinder_destructor(*cylinder, CODE_ERROR_MALLOC));
	ft_memset(cylinder->tube, 0, sizeof(t_hittable_tube));
	ft_memset(cylinder->disk[0], 0, sizeof(t_hittable_disk));
	ft_memset(cylinder->disk[1], 0, sizeof(t_hittable_disk));
	set_tube_of_cylinder(*cylinder->tube, cylinder_info, material);
	set_disk_of_cylinder(*cylinder->disk[0], cylinder_info, material, BOTTOM);
	set_disk_of_cylinder(*cylinder->disk[1], cylinder_info, material, TOP);
	return (CODE_OK);
}
*/

t_bool	hit_cylinder(t_hittable *hittable,
					t_ray *ray,
					t_minmax t,
					t_hit_record *rec)
{
	t_hittable_cylinder	*this;

	this = (t_hittable_cylinder *)hittable;
	if (this->tube.hit((t_hittable *)&this->tube, ray, t, rec))
		t.max = rec->t;
	if (this->disk[0].hit((t_hittable *)&this->disk[0], ray, t, rec))
		t.max = rec->t;
	if (this->disk[1].hit((t_hittable *)&this->disk[1], ray, t, rec))
		t.max = rec->t;
	if (val_is_near_zero(t.max - DOUBLE_INF))
		return (FALSE);
	return (TRUE);
}

t_hittable_cylinder	*cylinder_create(t_cylinder_info *cylinder_info,
										t_material *material)
{
	t_hittable_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_hittable_cylinder));
	if (!cylinder)
		return (NULL);
	ft_memset(cylinder, 0, sizeof(t_hittable_cylinder));
	cylinder->hit = hit_cylinder;
	cylinder->material = material;
	set_tube_of_cylinder(&cylinder->tube, cylinder_info, material);
	set_disk_of_cylinder(&cylinder->disk[0], cylinder_info, material, BOTTOM);
	set_disk_of_cylinder(&cylinder->disk[1], cylinder_info, material, TOP);
	return (cylinder);
}
