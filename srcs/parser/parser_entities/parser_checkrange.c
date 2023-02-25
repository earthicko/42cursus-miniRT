#include "libft.h"
#include "number.h"
#include "msgdef.h"
#include "parser_entities_internal.h"

// TODO: define infinity in header
t_bool	is_invalid_length(double len)
{
	if (len <= DOUBLE_E)
	{
		ft_dprintf(2, "%s: ratio "MSG_OUTOFRANGE"\n", EXEC_NAME,
			len, DOUBLE_E, 999999999);
		return (TRUE);
	}
	return (FALSE);
}

t_bool	is_invalid_ratio(double ratio)
{
	if (!(RANGE_MIN_RATIO <= ratio && ratio <= RANGE_MAX_RATIO))
	{
		ft_dprintf(2, "%s: ratio "MSG_OUTOFRANGE"\n", EXEC_NAME,
			ratio, RANGE_MIN_RATIO, RANGE_MAX_RATIO);
		return (TRUE);
	}
	return (FALSE);
}

t_bool	is_invalid_color(const t_color *color)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!(RANGE_MIN_COLOR <= color->i[i] && color->i[i] < RANGE_MAX_COLOR))
		{
			ft_dprintf(2, "%s: color "MSG_OUTOFRANGE"\n", EXEC_NAME,
				color->i[i], RANGE_MIN_COLOR, RANGE_MAX_COLOR);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

t_bool	is_invalid_normalized_vec3(const t_vec3 *vec)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!(RANGE_MIN_NORMALIZEDVEC3 <= vec->i[i]
				&& vec->i[i] <= RANGE_MAX_NORMALIZEDVEC3))
		{
			ft_dprintf(2, "%s: normalized vector component "MSG_OUTOFRANGE"\n",
				EXEC_NAME,
				vec->i[i], RANGE_MIN_NORMALIZEDVEC3, RANGE_MAX_NORMALIZEDVEC3);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

t_bool	is_invalid_fov(double fov)
{
	if (!(0.0 <= fov && fov <= 180.0))
	{
		ft_dprintf(2, "%s: fov "MSG_OUTOFRANGE"\n", EXEC_NAME,
			fov, RANGE_MIN_FOV, RANGE_MAX_FOV);
		return (TRUE);
	}
	return (FALSE);
}
