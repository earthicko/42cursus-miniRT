#include "libft.h"
#include "geometry.h"

void	m44_multiply_m44(t_matrix44 *m_out, t_matrix44 *m_a, t_matrix44 *m_b)
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
			m_out->i[row][col] = 0;
			n = 0;
			while (n < 4)
			{
				m_out->i[row][col] += m_a->i[row][n] * m_b->i[n][col];
				n++;
			}
			col++;
		}
		row++;
	}
}

void	m44_multiply_m44_inplace(t_matrix44 *m_out, t_matrix44 *m)
{
	t_matrix44	temp;

	m44_multiply_m44(&temp, m, m_out);
	ft_memcpy(m_out, &temp, sizeof(t_matrix44));
}

void	vec3_multiply_m44(t_vec3 *out, t_vec3 *v_a, t_matrix44 *m_b)
{
	double	(*m)[4];
	double	x;
	double	y;
	double	z;

	m = m_b->i;
	x = v_a->x;
	y = v_a->y;
	z = v_a->z;
	out->x = x * m[0][0] + y * m[1][0] + z * m[2][0] + m[3][0];
	out->y = x * m[0][1] + y * m[1][1] + z * m[2][1] + m[3][1];
	out->z = x * m[0][2] + y * m[1][2] + z * m[2][2] + m[3][2];
}
