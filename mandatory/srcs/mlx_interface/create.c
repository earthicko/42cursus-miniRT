#include <stdlib.h>
#include "libft.h"
#include "mlx_interface_internal.h"
#include "mlx.h"
#include "renderer.h"

int	exit_program(void *param)
{
	renderer_destroy((t_renderer *)param);
	exit(0);
}

t_display	*display_destroy(t_display *disp)
{
	void	*mlx;

	mlx = mlx_interface_get_mlx_ptr();
	if (mlx && disp->img)
		mlx_destroy_image(mlx, disp->img);
	if (mlx && disp->win)
		mlx_destroy_window(mlx, disp->win);
	if (disp->colors)
		free(disp->colors);
	free(disp);
	return (NULL);
}

static int	get_display_info(t_display *disp)
{
	int	i[3];

	disp->img_addr = mlx_get_data_addr(disp->img, i, i + 1, i + 2);
	disp->bpp = i[0];
	disp->nbytes = i[1];
	disp->endian = i[2];
	if (!disp->img_addr)
		return (CODE_ERROR_IO);
	return (CODE_OK);
}

static int	display_create_mlx(t_display *disp,
	int values[3], char *title)
{
	void	*mlx;

	mlx = mlx_init();
	if (!mlx)
		return (CODE_ERROR_GENERIC);
	mlxmanager(MLXMAN_SET, &mlx);
	disp->w = values[0];
	disp->h = values[1];
	disp->w_real = values[0] * values[2];
	disp->h_real = values[1] * values[2];
	disp->multiplier = values[2];
	disp->win = mlx_new_window(mlx, disp->w_real, disp->h_real, title);
	if (!disp->win)
		return (CODE_ERROR_GENERIC);
	disp->ratio = (double)disp->w / (double)disp->h;
	disp->img = mlx_new_image(mlx, disp->w_real, disp->h_real);
	if (!disp->img)
		return (CODE_ERROR_GENERIC);
	if (get_display_info(disp))
		return (CODE_ERROR_GENERIC);
	return (CODE_OK);
}

t_display	*display_create(int width, int height, int multiplier, char *title)
{
	t_display	*disp;
	int			values[3];

	disp = malloc(sizeof(t_display));
	if (!disp)
		return (NULL);
	ft_bzero(disp, sizeof(t_display));
	values[0] = width;
	values[1] = height;
	values[2] = multiplier;
	if (display_create_mlx(disp, values, title))
		return (display_destroy(disp));
	disp->colors = malloc(sizeof(t_color) * width * height);
	if (!disp->colors)
		return (display_destroy(disp));
	ft_bzero(disp->colors, sizeof(t_color) * width * height);
	return (disp);
}
