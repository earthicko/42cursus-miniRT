#include "mlx_interface.h"
#include "mlx.h"
#include <stddef.h>

int	display_start_buffer(t_display *disp)
{
	int	a[3];

	disp->img = mlx_new_image(disp->mlx, disp->w, disp->h);
	if (!disp->img)
		return (CODE_ERROR_IO);
	disp->img_addr = mlx_get_data_addr(disp->img, a, a + 1, a + 2);
	if (!disp->img_addr)
	{
		mlx_destroy_image(disp->mlx, disp->img);
		disp->img = NULL;
		return (CODE_ERROR_IO);
	}
	return (CODE_OK);
}

int	display_end_buffer(t_display *disp)
{
	if (!disp->img)
		return (CODE_ERROR_GENERIC);
	mlx_clear_window(disp->mlx, disp->win);
	mlx_put_image_to_window(disp->mlx, disp->win, disp->img, 0, 0);
	mlx_destroy_image(disp->mlx, disp->img);
	disp->img = NULL;
	disp->img_addr = NULL;
	return (CODE_OK);
}
