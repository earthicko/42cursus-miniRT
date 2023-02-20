#include "libft.h"
#include "geometry.h"

void	m44_translate(t_matrix44 *out, t_matrix44 *m, t_vec3 *delta)
{
	t_matrix44	translate;

	m44_init_identity(&translate);
	translate.i[3][0] = delta->x;
	translate.i[3][1] = delta->y;
	translate.i[3][2] = delta->z;
	m44_multiply_m44(out, m, &translate);
}

void	m44_translate_inplace(t_matrix44 *m, t_vec3 *delta)
{
	t_matrix44	temp;
	t_matrix44	translate;

	m44_init_identity(&translate);
	translate.i[3][0] = delta->x;
	translate.i[3][1] = delta->y;
	translate.i[3][2] = delta->z;
	m44_multiply_m44(&temp, m, &translate);
	ft_memcpy(m, &temp, sizeof(t_matrix44));
}
