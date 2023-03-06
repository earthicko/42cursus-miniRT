#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "print.h"
#include "builder_internal.h"

t_bool	is_box_with_material(const t_ptrarr *tokens);
int		add_box(t_scene *scene, t_box_info *info);

static int	parse_box_with_material(t_box_info *info,
				const t_ptrarr *tokens, t_scene *scene)
{
	int	i;

	build_vector(&info->cen, &tokens->data[1]);
	build_vector(&info->rotate_angles, &tokens->data[6]);
	info->aa_info.widths[0] = ft_atof(tokens->data[11]);
	info->aa_info.widths[1] = ft_atof(tokens->data[12]);
	info->aa_info.widths[2] = ft_atof(tokens->data[13]);
	if (is_invalid_length(info->aa_info.widths[0])
		|| is_invalid_length(info->aa_info.widths[1])
		|| is_invalid_length(info->aa_info.widths[2]))
		return (CODE_ERROR_DATA);
	i = 0;
	while (i < 6)
	{
		info->aa_info.mt[i]
			= scene_search_material(scene, tokens->data[14 + i]);
		if (!info->aa_info.mt[i])
			return (CODE_ERROR_DATA);
		i++;
	}
	return (CODE_OK);
}

int	build_box_with_material(const t_ptrarr *tokens, t_scene *scene)
{
	t_box_info	info;

	if (parse_box_with_material(&info, tokens, scene))
		return (CODE_ERROR_DATA);
	if (add_box(scene, &info))
		return (CODE_ERROR_MALLOC);
	printf("%s: ", __func__);
	print_box(ptrarr_getlast(scene->res.primitives));
	printf("\n");
	return (CODE_OK);
}
