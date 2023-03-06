/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:57:10 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMBER_H
# define NUMBER_H

# define DOUBLE_E	1e-8
# define DOUBLE_INF	999999999.9

typedef struct s_minmax
{
	double	min;
	double	max;
}	t_minmax;

double	rand_double(void);
double	rand_double_range(double min, double max);
int		rand_range(int min, int max);

int		is_near_zero(double num);
double	map_minmax(double x, const t_minmax *in, const t_minmax *out);
int		clamp_int(int x, int min, int max);
void	swap_double(double *a, double *b);

#endif
