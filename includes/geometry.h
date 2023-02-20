#ifndef GEOMETRY_H
# define GEOMETRY_H
# include "libft_def.h"

enum	e_axis
{
	AXIS_X = 0,
	AXIS_Y,
	AXIS_Z
};

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
	t_uint	color;
}	t_vec3;

typedef struct s_matrix44
{
	double	i[4][4];
}	t_matrix44;

void	m44_init_zero(t_matrix44 *m);
void	m44_init_identity(t_matrix44 *m);

void	vec3_multiply_m44(t_vec3 *out, t_vec3 *a, t_matrix44 *b);
void	m44_multiply_m44(t_matrix44 *out, t_matrix44 *a, t_matrix44 *b);
void	m44_multiply_m44_inplace(t_matrix44 *out, t_matrix44 *m);

void	m44_translate(t_matrix44 *out, t_matrix44 *m, t_vec3 *delta);
void	m44_translate_inplace(t_matrix44 *m, t_vec3 *delta);

void	m44_rotate(t_matrix44 *out, t_matrix44 *m, int axis_i, double a);
void	m44_rotate_inplace(t_matrix44 *m, int axis_i, double a);

#endif
