#include "libft.h"
#include "mlx_interface.h"
#include "mlx.h"
#include "renderer.h"
#include "settingman.h"
#include <stdlib.h>

int	exit_program(void *param)
{
	renderer_destroy((t_renderer *)param);
	system("leaks miniRT");
	exit(0);
}

t_display	*display_destroy(t_display *disp)
{
	if (disp->img)
		mlx_destroy_image(disp->mlx, disp->img);
	if (disp->win)
		mlx_destroy_window(disp->mlx, disp->win);
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
	int width, int height, char *title)
{
	disp->mlx = mlx_init();
	if (!disp->mlx)
		return (CODE_ERROR_GENERIC);
	disp->w = width;
	disp->h = height;
	disp->w_real = width * DISPLAY_MULTIPLIER;
	disp->h_real = height * DISPLAY_MULTIPLIER;
	disp->win = mlx_new_window(disp->mlx, disp->w_real, disp->h_real, title);
	if (!disp->win)
		return (CODE_ERROR_GENERIC);
	disp->ratio = (double)disp->w / (double)disp->h;
	disp->img = mlx_new_image(disp->mlx, disp->w_real, disp->h_real);
	if (!disp->img)
		return (CODE_ERROR_GENERIC);
	if (get_display_info(disp))
		return (CODE_ERROR_GENERIC);
	return (CODE_OK);
}

t_display	*display_create(int width, int height, char *title)
{
	t_display	*disp;

	disp = malloc(sizeof(t_display));
	if (!disp)
		return (NULL);
	ft_bzero(disp, sizeof(t_display));
	if (display_create_mlx(disp, width, height, title))
		return (display_destroy(disp));
	disp->colors = malloc(sizeof(t_color) * width * height);
	if (!disp->colors)
		return (display_destroy(disp));
	ft_bzero(disp->colors, sizeof(t_color) * width * height);
	return (disp);
}
