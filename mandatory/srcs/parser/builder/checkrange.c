/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkrange.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:50:18 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "number.h"
#include "builder_internal.h"

t_bool	is_invalid_length(double len)
{
	if (len <= DOUBLE_E)
		return (TRUE);
	return (FALSE);
}

t_bool	is_invalid_ratio(double ratio)
{
	if (!(RANGE_MIN_RATIO <= ratio && ratio <= RANGE_MAX_RATIO))
		return (TRUE);
	return (FALSE);
}

t_bool	is_invalid_color(const t_color *color)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!(RANGE_MIN_COLOR <= color->i[i] && color->i[i] < RANGE_MAX_COLOR))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	is_invalid_normalized_vec3(const t_vec3 *vec)
{
	double	len;

	len = vec3_get_len(vec);
	if (1.f - E_NORMALIZEDVEC3 < len && len < 1.f + E_NORMALIZEDVEC3)
		return (FALSE);
	return (TRUE);
}

t_bool	is_invalid_fov(double fov)
{
	if (!(0.0 <= fov && fov <= 180.0))
		return (TRUE);
	return (FALSE);
}
