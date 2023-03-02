#include <stdlib.h>
#include "libft.h"
#include "number.h"
#include "mlx.h"
#include "mlx_interface_internal.h"

void	imgwrapper_destroy(t_imgwrapper *img)
{
	void	*mlx;

	mlx = mlx_interface_get_mlx_ptr();
	if (img->colors)
		free(img->colors);
	free(img);
}

void	imgwrapper_getcolor(t_imgwrapper *img, t_color *out, const t_uv *uv)
{
	int				x;
	int				y;
	const t_minmax	uv_range = {0, 1};

	x = map_minmax(uv->i[0], &uv_range, &img->x_range);
	y = map_minmax(uv->i[1], &uv_range, &img->y_range);
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
	{
		vec3_setval(out, 0, 0, 0);
		return ;
	}
	*out = img->colors[img->width * y + x];
}
