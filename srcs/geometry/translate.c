#include "libft.h"
#include "geometry.h"

void	m44_translate(t_mtx44 *out, const t_mtx44 *m, const t_vec3 *delta)
{
	t_mtx44	translate;

	m44_init_identity(&translate);
	translate.i[3][0] = delta->i[0];
	translate.i[3][1] = delta->i[1];
	translate.i[3][2] = delta->i[2];
	m44_multiply_m44(out, m, &translate);
}

void	m44_translate_inplace(t_mtx44 *target, const t_vec3 *delta)
{
	t_mtx44	temp;
	t_mtx44	translate;

	m44_init_identity(&translate);
	translate.i[3][0] = delta->i[0];
	translate.i[3][1] = delta->i[1];
	translate.i[3][2] = delta->i[2];
	m44_multiply_m44(&temp, target, &translate);
	ft_memcpy(target, &temp, sizeof(t_mtx44));
}
