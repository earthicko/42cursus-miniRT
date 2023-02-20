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
	double	*v;

	m = m_b->i;
	v = v_a->i;
	out->i[0] = v[0] * m[0][0] + v[1] * m[1][0] + v[2] * m[2][0] + m[3][0];
	out->i[1] = v[0] * m[0][1] + v[1] * m[1][1] + v[2] * m[2][1] + m[3][1];
	out->i[2] = v[0] * m[0][2] + v[1] * m[1][2] + v[2] * m[2][2] + m[3][2];
}
