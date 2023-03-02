#include <stdlib.h>
#include "libft.h"
#include "number.h"
#include "mlx.h"
#include "mlx_interface_internal.h"

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

static void	copy_colors(t_imgwrapper *imgwrapper,
				char *data_addr, int bpp, int nbytes)
{
	int	o_height;
	int	o_width;
	int	x;
	int	y;

	y = 0;
	while (y < imgwrapper->height)
	{
		x = 0;
		while (x < imgwrapper->width)
		{
			o_height = nbytes * y;
			o_width = x * bpp / 8;
			imgwrapper->colors[imgwrapper->width * y + x]
				= map_color(*(int *)(data_addr + o_height + o_width));
			x++;
		}
		y++;
	}
}

static int	create_img(t_imgwrapper *imgwrapper, char *filename)
{
	void	*mlx;
	void	*img;
	char	*data_addr;
	int		vals[3];

	mlx = mlx_interface_get_mlx_ptr();
	if (!mlx)
		return (CODE_ERROR_GENERIC);
	img = mlx_xpm_file_to_image(mlx,
			filename, &imgwrapper->width, &imgwrapper->height);
	if (!img)
		return (CODE_ERROR_GENERIC);
	data_addr = mlx_get_data_addr(img, vals, vals + 1, vals + 2);
	if (!data_addr)
		return (CODE_ERROR_GENERIC);
	imgwrapper->colors = malloc(
			sizeof(t_color) * imgwrapper->width * imgwrapper->height);
	copy_colors(imgwrapper, data_addr, vals[0], vals[1]);
	mlx_destroy_image(mlx, img);
	return (CODE_OK);
}

t_imgwrapper	*imgwrapper_create(char *filename)
{
	t_imgwrapper	*imgwrapper;

	imgwrapper = malloc(sizeof(t_imgwrapper));
	if (!imgwrapper)
		return (NULL);
	ft_bzero(imgwrapper, sizeof(t_imgwrapper));
	imgwrapper->x_range.min = 0;
	imgwrapper->x_range.max = imgwrapper->width - 1;
	imgwrapper->y_range.min = 0;
	imgwrapper->y_range.max = imgwrapper->height - 1;
	if (create_img(imgwrapper, filename))
	{
		imgwrapper_destroy(imgwrapper);
		return (NULL);
	}
	return (imgwrapper);
}
