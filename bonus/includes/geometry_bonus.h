/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRY_BONUS_H
# define GEOMETRY_BONUS_H

# include "libft_def.h"

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

typedef struct s_mtx44
{
	double	i[4][4];
}	t_mtx44;

void	vec3_setval(t_vec3 *out, double a, double b, double c);
void	vec2_setval(t_vec2 *out, double a, double b);

void	vec3_add_vec3(t_vec3 *out, const t_vec3 *a, const t_vec3 *b);
void	vec3_sub_vec3(t_vec3 *out, const t_vec3 *a, const t_vec3 *b);
void	vec3_add_vec3_inplace(t_vec3 *target, const t_vec3 *b);
void	vec3_sub_vec3_inplace(t_vec3 *target, const t_vec3 *b);

double	vec3_dot_vec3(const t_vec3 *a, const t_vec3 *b);
void	vec3_cross_vec3(t_vec3 *out, const t_vec3 *a, const t_vec3 *b);

void	vec3_mult_num(t_vec3 *out, const t_vec3 *a, double b);
void	vec3_mult_num_inplace(t_vec3 *target, double b);
void	vec3_mult_component_vec3(t_vec3 *out, const t_vec3 *a, const t_vec3 *b);
void	vec3_mult_component_vec3_inplace(t_vec3 *target, const t_vec3 *a);

void	vec3_reflect(t_vec3 *out, const t_vec3 *in, const t_vec3 *n);
void	vec3_refract(t_vec3 *out, const t_vec3 *in, const t_vec3 *n, double r);

void	m44_init_zero(t_mtx44 *target);
void	m44_init_identity(t_mtx44 *target);
void	m44_get_inverse(t_mtx44 *out, const t_mtx44 *in);

void	vec3_multiply_m44(t_vec3 *out, const t_vec3 *a, const t_mtx44 *b);
void	vec3_multiply_m44_inplace(t_vec3 *target, const t_mtx44 *a);
void	m44_multiply_m44(t_mtx44 *out, const t_mtx44 *a, const t_mtx44 *b);
void	m44_multiply_m44_inplace(t_mtx44 *target, const t_mtx44 *m);

void	m44_translate(t_mtx44 *out, const t_mtx44 *m, const t_vec3 *delta);
void	m44_translate_inplace(t_mtx44 *target, const t_vec3 *delta);

void	m44_rotate(t_mtx44 *out, const t_mtx44 *m, int axis_i, double a);
void	m44_rotate_inplace(t_mtx44 *m, int axis_i, double a);

t_bool	vec3_is_near_zero(const t_vec3 *in);
double	vec3_get_len(const t_vec3 *in);
double	vec3_get_len_sq(const t_vec3 *in);
void	vec3_get_unit(t_vec3 *out, const t_vec3 *in);
void	vec3_unitize(t_vec3 *target);
void	vec3_rand(t_vec3 *out, double min, double max);
void	vec3_get_random_in_unit_sphere(t_vec3 *out);
void	vec3_get_random_unit(t_vec3 *out);
void	vec3_rand_ts(t_vec3 *out, double min, double max);
void	vec3_get_random_in_unit_sphere_ts(t_vec3 *out);
void	vec3_get_random_unit_ts(t_vec3 *out);
void	vec3_min(t_vec3 *out, const t_vec3 *a, const t_vec3 *b);
void	vec3_max(t_vec3 *out, const t_vec3 *a, const t_vec3 *b);

#endif
