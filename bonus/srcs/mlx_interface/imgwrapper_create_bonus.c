/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imgwrapper_create_bonus.c                          :+:      :+:    :+:   */
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

static t_color	map_color(int color)
{
	t_uchar			rgb[3];
	t_color			mappedcolor;
	const t_minmax	in = {0, 255};
	const t_minmax	out = {0, 1};

	rgb[0] = (t_uchar)(color >> 16);
	rgb[1] = (t_uchar)(color >> 8);
	rgb[2] = (t_uchar)(color);
	mappedcolor.i[0] = map_minmax((double)rgb[0], &in, &out);
	mappedcolor.i[1] = map_minmax((double)rgb[1], &in, &out);
	mappedcolor.i[2] = map_minmax((double)rgb[2], &in, &out);
	return (mappedcolor);
}

static void	copy_colors(t_imgwrapper *img, char *data_addr, int bpp, int nbytes)
{
	int	o_height;
	int	o_width;
	int	x;
	int	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			o_height = nbytes * y;
			o_width = x * bpp / 8;
			img->colors[img->width * (img->height - y - 1) + x]
				= map_color(*(int *)(data_addr + o_height + o_width));
			x++;
		}
		y++;
	}
}

static int	get_data_addr(t_imgwrapper *imgwrapper,
				void **img, char **data_addr, int vals[3])
{
	void	*mlx;

	mlx = mlx_interface_get_mlx_ptr();
	if (!mlx)
		return (CODE_ERROR_GENERIC);
	*img = mlx_xpm_file_to_image(mlx,
			imgwrapper->filename, &imgwrapper->width, &imgwrapper->height);
	if (!*img)
		return (CODE_ERROR_GENERIC);
	*data_addr = mlx_get_data_addr(*img, vals, vals + 1, vals + 2);
	if (!*data_addr)
		return (CODE_ERROR_GENERIC);
	return (CODE_OK);
}

int	imgwrapper_load(t_imgwrapper *imgwrapper)
{
	void	*img;
	char	*data_addr;
	int		vals[3];

	if (get_data_addr(imgwrapper, &img, &data_addr, vals))
		return (CODE_ERROR_GENERIC);
	imgwrapper->x_range.min = 0;
	imgwrapper->x_range.max = imgwrapper->width - 1;
	imgwrapper->y_range.min = 0;
	imgwrapper->y_range.max = imgwrapper->height - 1;
	imgwrapper->colors = malloc(
			sizeof(t_color) * imgwrapper->width * imgwrapper->height);
	if (!imgwrapper->colors)
		return (CODE_ERROR_MALLOC);
	copy_colors(imgwrapper, data_addr, vals[0], vals[1]);
	mlx_destroy_image(mlx_interface_get_mlx_ptr(), img);
	if (imgwrapper_transform(imgwrapper))
		printf("%s: Failed to transform image %s.\n", __func__,
			imgwrapper->filename);
	printf("%s: Image %s loaded.\n", __func__, imgwrapper->filename);
	return (CODE_OK);
}

t_imgwrapper	*imgwrapper_create(char *filename, int rotation, int flip)
{
	t_imgwrapper	*imgwrapper;

	imgwrapper = malloc(sizeof(t_imgwrapper));
	if (!imgwrapper)
		return (NULL);
	ft_bzero(imgwrapper, sizeof(t_imgwrapper));
	imgwrapper->filename = ft_strdup(filename);
	if (!imgwrapper)
	{
		imgwrapper_destroy(imgwrapper);
		return (NULL);
	}
	imgwrapper->rotation = rotation;
	imgwrapper->flip = flip;
	if (imgwrapper_load(imgwrapper))
		imgwrapper->colors = NULL;
	return (imgwrapper);
}
