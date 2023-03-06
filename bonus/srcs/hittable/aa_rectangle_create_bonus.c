#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "geometry_bonus.h"
#include "material_bonus.h"
#include "hittable_internal_bonus.h"

t_bool	hit_aa_rectangle(t_hittable *hittable,
			const t_ray *ray,
			t_minmax t,
			t_hit_record *rec);

static void	set_bbox(t_hittable_aa_rectangle *aa_rect)
{
	t_point	min;
	t_point	max;

	min.i[aa_rect->axis] = aa_rect->offset - DOUBLE_E;
	max.i[aa_rect->axis] = aa_rect->offset + DOUBLE_E;
	min.i[aa_rect->other_axis[0]] = aa_rect->range[0].min;
	max.i[aa_rect->other_axis[0]] = aa_rect->range[0].max;
	min.i[aa_rect->other_axis[1]] = aa_rect->range[1].min;
	max.i[aa_rect->other_axis[1]] = aa_rect->range[1].max;
	bbox_init(&aa_rect->bbox, min, max);
}

static void	hittable_aa_rectangle_set_dir(t_hittable_aa_rectangle *aa_rect,
			t_aa_rectangle_info *info)
{
	const int	other_axises[3][2] = {{1, 2}, {2, 0}, {0, 1}};

	aa_rect->axis = info->axis;
	aa_rect->offset = info->offset;
	aa_rect->other_axis[0] = other_axises[info->axis][0];
	aa_rect->other_axis[1] = other_axises[info->axis][1];
	aa_rect->range[0] = info->range[0];
	aa_rect->range[1] = info->range[1];
	if (info->flip)
		aa_rect->outward_norm.i[aa_rect->axis] = -1;
	else
		aa_rect->outward_norm.i[aa_rect->axis] = +1;
	aa_rect->outward_norm.i[aa_rect->other_axis[0]] = 0;
	aa_rect->outward_norm.i[aa_rect->other_axis[1]] = 0;
}

t_hittable	*hittable_aa_rectangle_create(t_aa_rectangle_info info,
											t_material *material)
{
	t_hittable_aa_rectangle	*aa_rect;

	if (info.axis < AXIS_X || info.axis > AXIS_Z)
		return (NULL);
	if (info.range[0].min > info.range[0].max
		|| info.range[1].min > info.range[1].max)
		return (NULL);
	aa_rect = malloc(sizeof(t_hittable_aa_rectangle));
	if (!aa_rect)
		return (NULL);
	ft_bzero(aa_rect, sizeof(t_hittable_aa_rectangle));
	aa_rect->destroy = hittable_destroy;
	aa_rect->hit = hit_aa_rectangle;
	aa_rect->material = material;
	hittable_aa_rectangle_set_dir(aa_rect, &info);
	set_bbox(aa_rect);
	return ((t_hittable *)aa_rect);
}
