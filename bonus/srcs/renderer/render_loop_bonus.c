/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer_internal_bonus.h"

void	renderer_render_loop_multithread(t_renderer_worker *worker)
{
	int	x;
	int	y;

	y = worker->y_begin;
	while (y < worker->y_end)
	{
		x = 0;
		while (x < worker->renderer->disp->w)
		{
			renderer_render_pixel(worker->renderer, x, y);
			x++;
		}
		y++;
	}
}

void	renderer_render_loop(t_renderer *renderer)
{
	int	x;
	int	y;

	y = 0;
	while (y < renderer->disp->h)
	{
		x = 0;
		while (x < renderer->disp->w)
		{
			renderer_render_pixel(renderer, x, y);
			x++;
		}
		y++;
	}
}
