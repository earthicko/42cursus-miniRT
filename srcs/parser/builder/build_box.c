#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "print.h"
#include "builder_internal.h"

t_bool	is_box_with_color(const t_ptrarr *tokens);
t_bool	is_box_with_material(const t_ptrarr *tokens);
int		build_box_with_color(const t_ptrarr *tokens, t_scene *scene);
int		build_box_with_material(const t_ptrarr *tokens, t_scene *scene);

int	add_box(t_scene *scene, t_box_info *info)
{
	t_hittable	*aa_box;
	t_hittable	*box;

	aa_box = hittable_aa_box_create(&info->aa_info);
	if (!aa_box)
		return (CODE_ERROR_MALLOC);
	if (ptrarr_append(scene->res.primitives, aa_box))
	{
		aa_box->destroy(aa_box);
		return (CODE_ERROR_MALLOC);
	}
	box = hittable_transform_create(aa_box,
			info->cen, info->x_axis, deg_to_rad(info->x_angle));
	if (!box)
		return (CODE_ERROR_MALLOC);
	if (ptrarr_append(scene->res.primitives, box))
	{
		box->destroy(box);
		return (CODE_ERROR_MALLOC);
	}
	if (hittable_list_append(scene->world, box)
		|| hittable_list_append(scene->objects, box))
		return (CODE_ERROR_MALLOC);
	return (CODE_OK);
}

int	build_box(const t_ptrarr *tokens, t_scene *scene)
{
	if (is_box_with_color(tokens))
		return (build_box_with_color(tokens, scene));
	if (is_box_with_material(tokens))
		return (build_box_with_material(tokens, scene));
	return (CODE_ERROR_GENERIC);
}
