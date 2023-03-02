#include "mlx.h"
#include "mlx_interface.h"
#include "settingman.h"

static void	display_putpixel_forreal(t_display *disp, t_pixel p)
{
	int	o_height;
	int	o_width;

	o_height = disp->nbytes * p.y;
	o_width = p.x * disp->bpp / 8;
	*(t_uint *)(disp->img_addr + o_height + o_width) = p.color;
}

void	display_putpixel(t_display *disp, t_pixel p)
{
	int		x_offset;
	int		y_offset;
	t_pixel	p_real;

	if (p.x < 0 || p.x >= disp->w)
		return ;
	if (p.y < 0 || p.y >= disp->h)
		return ;
	x_offset = 0;
	while (x_offset < disp->multiplier)
	{
		y_offset = 0;
		while (y_offset < disp->multiplier)
		{
			p_real.x = p.x * disp->multiplier + x_offset;
			p_real.y = p.y * disp->multiplier + y_offset;
			p_real.color = p.color;
			display_putpixel_forreal(disp, p_real);
			y_offset++;
		}
		x_offset++;
	}
}

void	display_putimage(t_display *disp)
{
	mlx_put_image_to_window(disp->mlx, disp->win, disp->img, 0, 0);
}
