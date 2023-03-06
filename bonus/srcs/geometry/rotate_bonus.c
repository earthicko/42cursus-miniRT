/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "geometry_bonus.h"
#include <math.h>

static void	matrix44_rotate_x(t_mtx44 *out, const t_mtx44 *m, double theta)
{
	t_mtx44	rotate;

	m44_init_zero(&rotate);
	rotate.i[0][0] = 1;
	rotate.i[1][1] = cos(theta);
	rotate.i[1][2] = sin(theta);
	rotate.i[2][1] = -sin(theta);
	rotate.i[2][2] = cos(theta);
	rotate.i[3][3] = 1;
	m44_multiply_m44(out, m, &rotate);
}

static void	matrix44_rotate_y(t_mtx44 *out, const t_mtx44 *m, double theta)
{
	t_mtx44	rotate;

	m44_init_zero(&rotate);
	rotate.i[0][0] = cos(theta);
	rotate.i[0][2] = -sin(theta);
	rotate.i[1][1] = 1;
	rotate.i[2][0] = sin(theta);
	rotate.i[2][2] = cos(theta);
	rotate.i[3][3] = 1;
	m44_multiply_m44(out, m, &rotate);
}

static void	matrix44_rotate_z(t_mtx44 *out, const t_mtx44 *m, double theta)
{
	t_mtx44	rotate;

	m44_init_zero(&rotate);
	rotate.i[0][0] = cos(theta);
	rotate.i[0][1] = sin(theta);
	rotate.i[1][0] = -sin(theta);
	rotate.i[1][1] = cos(theta);
	rotate.i[2][2] = 1;
	rotate.i[3][3] = 1;
	m44_multiply_m44(out, m, &rotate);
}

void	m44_rotate(t_mtx44 *out, const t_mtx44 *m, int axis_i, double theta)
{
	if (axis_i == AXIS_X)
		matrix44_rotate_x(out, m, theta);
	else if (axis_i == AXIS_Y)
		matrix44_rotate_y(out, m, theta);
	else if (axis_i == AXIS_Z)
		matrix44_rotate_z(out, m, theta);
}

void	m44_rotate_inplace(t_mtx44 *target, int axis_i, double theta)
{
	t_mtx44	temp;

	m44_rotate(&temp, target, axis_i, theta);
	ft_memcpy(target, &temp, sizeof(t_mtx44));
}
