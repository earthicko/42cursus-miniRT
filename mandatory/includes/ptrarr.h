/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptrarr.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PTRARR_H
# define PTRARR_H

# include "libft_def.h"

# define PTRARR_INITIAL_CAP 1

typedef struct s_ptrarr
{
	int			len;
	int			cap;
	const void	**data;
}	t_ptrarr;

t_ptrarr	*ptrarr_create(void);
t_ptrarr	*ptrarr_destroy(t_ptrarr *ptrarr, void (*destroyer)(void *));
int			ptrarr_expand(t_ptrarr *ptrarr);
int			ptrarr_append(t_ptrarr *ptrarr, const void *data);
void		ptrarr_destroy_all(t_ptrarr *ptrarr, void (*destroyer)(void *));
void		*ptrarr_get(const t_ptrarr *arr, int i);
void		*ptrarr_getfirst(const t_ptrarr *arr);
void		*ptrarr_getlast(const t_ptrarr *arr);

#endif
