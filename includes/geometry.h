#ifndef GEOMETRY_H
# define GEOMETRY_H
# include "libft_def.h"

# define DOUBLE_E 1e-8

enum	e_axis
{
	AXIS_X = 0,
	AXIS_Y,
	AXIS_Z
};

typedef struct s_vec2
{
	double	i[2];
}	t_vec2;

typedef t_vec2	t_uv;

typedef struct s_vec3
{
	double	i[3];
}	t_vec3;

typedef t_vec3	t_color;
typedef t_vec3	t_point;

typedef struct s_matrix44
{
	double	i[4][4];
}	t_matrix44;

void	vec3_add_vec3(t_vec3 *out, t_vec3 *a, t_vec3 *b);
void	vec3_sub_vec3(t_vec3 *out, t_vec3 *a, t_vec3 *b);
void	vec3_add_vec3_inplace(t_vec3 *a, t_vec3 *b);
void	vec3_sub_vec3_inplace(t_vec3 *a, t_vec3 *b);

double	vec3_dot_vec3(t_vec3 *a, t_vec3 *b);
void	vec3_cross_vec3(t_vec3 *out, t_vec3 *a, t_vec3 *b);

void	vec3_mult_num(t_vec3 *out, t_vec3 *a, double b);
void	vec3_mult_num_inplace(t_vec3 *a, double b);

void	m44_init_zero(t_matrix44 *m);
void	m44_init_identity(t_matrix44 *m);

void	vec3_multiply_m44(t_vec3 *out, t_vec3 *a, t_matrix44 *b);
void	m44_multiply_m44(t_matrix44 *out, t_matrix44 *a, t_matrix44 *b);
void	m44_multiply_m44_inplace(t_matrix44 *out, t_matrix44 *m);

void	m44_translate(t_matrix44 *out, t_matrix44 *m, t_vec3 *delta);
void	m44_translate_inplace(t_matrix44 *m, t_vec3 *delta);

void	m44_rotate(t_matrix44 *out, t_matrix44 *m, int axis_i, double a);
void	m44_rotate_inplace(t_matrix44 *m, int axis_i, double a);

t_bool	vec3_is_near_zero(t_vec3 *in);
double	vec3_get_len(t_vec3 *in);
double	vec3_get_len_sq(t_vec3 *in);
void	vec3_get_unit(t_vec3 *out, t_vec3 *in);
void	vec3_unitize(t_vec3 *target);
void	vec3_rand(t_vec3 *out, double min, double max);
void	vec3_get_random_in_unit_sphere(t_vec3 *out);
void	vec3_get_random_unit(t_vec3 *out);

#endif
