/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiply.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "geometry.h"

void	m44_multiply_m44(t_mtx44 *out, const t_mtx44 *a, const t_mtx44 *b)
{
	int		row;
	int		col;
	int		n;

	row = 0;
	while (row < 4)
	{
		col = 0;
		while (col < 4)
		{
			out->i[row][col] = 0;
			n = 0;
			while (n < 4)
			{
				out->i[row][col] += a->i[row][n] * b->i[n][col];
				n++;
			}
			col++;
		}
		row++;
	}
}

void	m44_multiply_m44_inplace(t_mtx44 *out, const t_mtx44 *m)
{
	t_mtx44	temp;

	m44_multiply_m44(&temp, m, out);
	ft_memcpy(out, &temp, sizeof(t_mtx44));
}

void	vec3_multiply_m44(t_vec3 *out, const t_vec3 *a, const t_mtx44 *b)
{
	const	double	(*m)[4];
	const double	*v;

	m = b->i;
	v = a->i;
	out->i[0] = v[0] * m[0][0] + v[1] * m[1][0] + v[2] * m[2][0] + m[3][0];
	out->i[1] = v[0] * m[0][1] + v[1] * m[1][1] + v[2] * m[2][1] + m[3][1];
	out->i[2] = v[0] * m[0][2] + v[1] * m[1][2] + v[2] * m[2][2] + m[3][2];
}

void	vec3_multiply_m44_inplace(t_vec3 *target, const t_mtx44 *a)
{
	t_vec3	out;

	vec3_multiply_m44(&out, target, a);
	*target = out;
}
