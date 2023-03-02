#include <stdlib.h>
#include "number.h"
#include "mlx.h"
#include "mlx_interface.h"

void	imgwrapper_destroy(t_imgwrapper *img)
{
	mlx_destroy_image(img->disp->mlx, img->mlx_img);
	free(img);
}

// #include <stdio.h>
// #include "print.h"
t_imgwrapper	*imgwrapper_create(t_display *disp, char *filename)
{
	t_imgwrapper	*imgwrapper;

	imgwrapper = malloc(sizeof(t_imgwrapper));
	if (!imgwrapper)
		return (NULL);
	imgwrapper->mlx_img = mlx_xpm_file_to_image(disp->mlx,
			filename, &imgwrapper->width, &imgwrapper->height);
	if (!imgwrapper->mlx_img)
	{
		free(imgwrapper);
		return (NULL);
	}
	imgwrapper->x_range.min = 0;
	imgwrapper->x_range.max = imgwrapper->width - 1;
	imgwrapper->y_range.min = 0;
	imgwrapper->y_range.max = imgwrapper->height - 1;
	imgwrapper->disp = disp;
	// printf("height %d, width %d\n", imgwrapper->height, imgwrapper->width);
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
	// printf("uv (%.2f, %.2f) -> xy (%d, %d)\n", uv->i[0], uv->i[1], x, y);
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (-1);
	o_height = img->disp->nbytes * y;
	o_width = x * img->disp->bpp / 8;
	// printf("height %d, width %d\n", o_height, o_width);
	return (*(int *)(img->disp->img_addr + o_height + o_width));
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
	// printf("color is %d, %d, %d (#%x%x%x)\n", rgb[0], rgb[1], rgb[2], rgb[0], rgb[1], rgb[2]);
	out->i[0] = map_minmax((double)rgb[0], &color_range, &uv_range);
	out->i[1] = map_minmax((double)rgb[1], &color_range, &uv_range);
	out->i[2] = map_minmax((double)rgb[2], &color_range, &uv_range);
}
