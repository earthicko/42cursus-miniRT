#include <stdlib.h>
#include "libft.h"
#include "number.h"
#include "mlx.h"
#include "mlx_interface_internal.h"

void	imgwrapper_destroy(t_imgwrapper *img)
{
	void	*mlx;

	mlx = mlx_interface_get_mlx_ptr();
	if (mlx && img->img)
		mlx_destroy_image(mlx, img->img);
	free(img);
}

static int	create_img(t_imgwrapper *imgwrapper, char *filename)
{
	void	*mlx;

	mlx = mlx_interface_get_mlx_ptr();
	if (!mlx)
		return (CODE_ERROR_GENERIC);
	imgwrapper->img = mlx_xpm_file_to_image(mlx,
			filename, &imgwrapper->width, &imgwrapper->height);
	if (!imgwrapper->img)
		return (CODE_ERROR_GENERIC);
	imgwrapper->data_addr = mlx_get_data_addr(imgwrapper->img,
			&imgwrapper->bpp, &imgwrapper->nbytes, &imgwrapper->endian);
	if (!imgwrapper->data_addr)
		return (CODE_ERROR_GENERIC);
	return (CODE_OK);
}

t_imgwrapper	*imgwrapper_create(char *filename)
{
	t_imgwrapper	*imgwrapper;

	imgwrapper = malloc(sizeof(t_imgwrapper));
	if (!imgwrapper)
		return (NULL);
	ft_bzero(imgwrapper, sizeof(t_imgwrapper));
	if (create_img(imgwrapper, filename))
	{
		imgwrapper_destroy(imgwrapper);
		return (NULL);
	}
	imgwrapper->x_range.min = 0;
	imgwrapper->x_range.max = imgwrapper->width - 1;
	imgwrapper->y_range.min = 0;
	imgwrapper->y_range.max = imgwrapper->height - 1;
	return (imgwrapper);
}

static int	get_color(t_imgwrapper *img, const t_uv *uv)
{
	int				o_height;
	int				o_width;
	int				x;
	int				y;
	const t_minmax	uv_range = {0, 1};

	x = (int)map_minmax(uv->i[0], &uv_range, &img->x_range);
	y = (int)map_minmax(uv->i[1], &uv_range, &img->y_range);
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (-1);
	o_height = img->nbytes * y;
	o_width = x * img->bpp / 8;
	return (*(int *)(img->data_addr + o_height + o_width));
}

void	imgwrapper_getcolor(t_imgwrapper *img, t_color *out, const t_uv *uv)
{
	int				color;
	t_uchar			rgb[3];
	const t_minmax	uv_range = {0, 1};
	const t_minmax	color_range = {0, 255};

	color = get_color(img, uv);
	if (color < 0)
	{
		vec3_setval(out, 0, 0, 0);
		return ;
	}
	rgb[0] = (t_uchar)(color >> 16);
	rgb[1] = (t_uchar)(color >> 8);
	rgb[2] = (t_uchar)(color);
	out->i[0] = map_minmax((double)rgb[0], &color_range, &uv_range);
	out->i[1] = map_minmax((double)rgb[1], &color_range, &uv_range);
	out->i[2] = map_minmax((double)rgb[2], &color_range, &uv_range);
}
