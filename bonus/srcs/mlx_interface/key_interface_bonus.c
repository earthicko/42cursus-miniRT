/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_interface_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_interface_bonus.h"
#include "renderer_bonus.h"

int	mlx_key_interface(int k, void *param)
{
	t_renderer	*renderer;

	renderer = param;
	(void)renderer;
	if (k == KEYCODE_ESC)
		exit_program(param);
	return (0);
}
