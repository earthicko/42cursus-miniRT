/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imgwrapper_transform_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "number_bonus.h"
#include "mlx.h"
#include "mlx_interface_internal_bonus.h"

void	imgwrapper_flip(t_imgwrapper *img)
{
	t_color	buf;
	int		x;
	int		y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width / 2)
		{
			buf = img->colors[img->width * y + x];
			img->colors[img->width * y + x]
				= img->colors[img->width * y + (img->width - x - 1)];
			img->colors[img->width * y + (img->width - x - 1)] = buf;
			x++;
		}
		y++;
	}
}

static void	rotate_loop(t_imgwrapper *img, t_color *buf)
{
	int		x;
	int		y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			buf[img->height * x + (img->height - y - 1)]
				= img->colors[img->width * y + x];
			x++;
		}
		y++;
	}
}

int	imgwrapper_rotate(t_imgwrapper *img)
{
	t_color		*buf;
	int			temp_i;
	t_minmax	temp_m;

	buf = malloc(sizeof(t_color) * img->width * img->height);
	if (!buf)
		return (CODE_ERROR_MALLOC);
	rotate_loop(img, buf);
	temp_i = img->width;
	img->width = img->height;
	img->height = temp_i;
	temp_m = img->x_range;
	img->x_range = img->y_range;
	img->y_range = temp_m;
	free(img->colors);
	img->colors = buf;
	return (CODE_OK);
}

int	imgwrapper_transform(t_imgwrapper *imgwrapper)
{
	int	i;

	if (imgwrapper->flip)
	{
		imgwrapper_flip(imgwrapper);
		imgwrapper->flip = 0;
	}
	while (imgwrapper->rotation < 0)
		imgwrapper->rotation += 4;
	i = 0;
	while (i < imgwrapper->rotation % 4)
	{
		if (imgwrapper_rotate(imgwrapper))
		{
			imgwrapper->rotation -= i;
			return (CODE_ERROR_MALLOC);
		}
		i++;
	}
	imgwrapper->rotation = 0;
	return (CODE_OK);
}
