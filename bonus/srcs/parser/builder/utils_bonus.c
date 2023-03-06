/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "number_bonus.h"
#include "geometry_bonus.h"

void	build_vector(t_vec3 *out, const void **token_start)
{
	out->i[0] = ft_atof(token_start[0]);
	out->i[1] = ft_atof(token_start[2]);
	out->i[2] = ft_atof(token_start[4]);
}

void	map_color(t_color *color)
{
	int				i;
	const t_minmax	in = {0, 255};
	const t_minmax	out = {0, 1};

	i = 0;
	while (i < 3)
	{
		color->i[i] = map_minmax(color->i[i], &in, &out);
		i++;
	}
}
