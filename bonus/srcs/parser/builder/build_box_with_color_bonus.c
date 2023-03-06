/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_box_with_color_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "print_bonus.h"
#include "builder_internal_bonus.h"

t_bool	is_box_with_color(const t_ptrarr *tokens);
t_bool	is_box_with_material(const t_ptrarr *tokens);
int		add_box(t_scene *scene, t_box_info *info);

static int	parse_box_with_color(
				t_box_info *info, t_color *color, const t_ptrarr *tokens)
{
	build_vector(&info->cen, &tokens->data[1]);
	build_vector(&info->rotate_angles, &tokens->data[6]);
	info->aa_info.widths[0] = ft_atof(tokens->data[11]);
	info->aa_info.widths[1] = ft_atof(tokens->data[12]);
	info->aa_info.widths[2] = ft_atof(tokens->data[13]);
	build_vector(color, &tokens->data[14]);
	if (is_invalid_color(color)
		|| is_invalid_length(info->aa_info.widths[0])
		|| is_invalid_length(info->aa_info.widths[1])
		|| is_invalid_length(info->aa_info.widths[2]))
		return (CODE_ERROR_DATA);
	map_color(color);
	return (CODE_OK);
}

int	build_box_with_color(const t_ptrarr *tokens, t_scene *scene)
{
	t_box_info	info;
	t_color		color;
	int			i;

	if (parse_box_with_color(&info, &color, tokens))
		return (CODE_ERROR_DATA);
	if (add_texture_solid(scene, "", color))
		return (CODE_ERROR_MALLOC);
	if (add_material_lambertian(scene, "", ptrarr_getlast(scene->res.textures)))
		return (CODE_ERROR_MALLOC);
	i = 0;
	while (i < 6)
	{
		info.aa_info.mt[i] = ptrarr_getlast(scene->res.materials);
		i++;
	}
	if (add_box(scene, &info))
		return (CODE_ERROR_MALLOC);
	printf("%s: ", __func__);
	print_box(ptrarr_getlast(scene->res.primitives));
	printf("\n");
	return (CODE_OK);
}
