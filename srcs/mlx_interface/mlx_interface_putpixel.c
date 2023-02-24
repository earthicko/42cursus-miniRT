#include "mlx_interface.h"

void	display_putpixel(t_display *disp, t_pixel p)
{
	int	o_height;
	int	o_width;

	if (p.x < 0 || p.x >= disp->w)
		return ;
	if (p.y < 0 || p.y >= disp->h)
		return ;
	o_height = disp->nbytes * p.y;
	o_width = p.x * disp->bpp / 8;
	*(t_uint *)(disp->img_addr + o_height + o_width) = p.color;
}
