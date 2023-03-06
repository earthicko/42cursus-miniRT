#include "display_internal.h"
#include "settingman.h"

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
			disp->image[p_real.y * disp->w + p_real.x] = p_real.color;
			y_offset++;
		}
		x_offset++;
	}
}
