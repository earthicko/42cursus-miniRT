/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:55:37 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "renderer_internal.h"
#include "settingman.h"

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

static t_bool	should_update(int max_samples, int n_samples, int freq)
{
	if (n_samples >= max_samples
		|| n_samples == 1
		|| n_samples % freq == 0)
		return (TRUE);
	return (FALSE);
}

static void	renderer_render_update(t_renderer *renderer, int n_samples)
{
	static int	update_count;

	if (should_update(RENDERER_N_SAMPLES, n_samples, RENDERER_UPDATE_FREQ_SHOW))
	{
		renderer_write_color(renderer, n_samples);
		display_putimage(renderer->disp);
		update_count++;
	}
}

int	renderer_render(void *param)
{
	t_renderer	*renderer;
	static int	n_samples_so_far;
	static int	render_finished;

	renderer = (t_renderer *)param;
	if (render_finished == 1)
		return (0);
	if (n_samples_so_far >= RENDERER_N_SAMPLES)
	{
		render_finished = 1;
		renderer_render_update(renderer, n_samples_so_far);
		return (0);
	}
	renderer_render_loop(renderer);
	n_samples_so_far++;
	renderer_render_update(renderer, n_samples_so_far);
	return (0);
}
