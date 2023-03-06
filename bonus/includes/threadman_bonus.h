/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadman_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADMAN_BONUS_H
# define THREADMAN_BONUS_H

enum e_threadmanmode
{
	CREATE = 0,
	JOIN,
	GETID
};

int	threadman(int mode, int idx, void *(*routine)(void *), void *arg);

#endif
