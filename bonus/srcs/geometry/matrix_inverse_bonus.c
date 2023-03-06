/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inverse_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry_bonus.h"

int	forward_elimination(t_mtx44 *copy, t_mtx44 *out);

static void	set_diagonal(t_mtx44 *copy, t_mtx44 *out)
{
	int		i;
	int		j;
	double	div;

	i = 0;
	while (i < 4)
	{
		div = copy->i[i][i];
		j = 0;
		while (j < 4)
		{
			copy->i[i][j] = copy->i[i][j] / div;
			out->i[i][j] = out->i[i][j] / div;
			j++;
		}
		copy->i[i][i] = 1.0;
		i++;
	}
}

static void	eliminate_above_diagonal(t_mtx44 *copy, t_mtx44 *out)
{
	int		i;
	int		j;
	int		k;
	double	constant;

	i = 0;
	while (i < 3)
	{
		j = i + 1;
		while (j < 4)
		{
			constant = copy->i[i][j];
			k = 0;
			while (k < 4)
			{
				copy->i[i][k] -= copy->i[j][k] * constant;
				out->i[i][k] -= out->i[j][k] * constant;
				k++;
			}
			copy->i[i][j] = 0.0;
			j++;
		}
		i++;
	}
}

void	m44_get_inverse(t_mtx44 *out, const t_mtx44 *in)
{
	t_mtx44	copy;

	copy = *in;
	m44_init_identity(out);
	if (forward_elimination(&copy, out))
	{
		m44_init_identity(out);
		return ;
	}
	set_diagonal(&copy, out);
	eliminate_above_diagonal(&copy, out);
}
