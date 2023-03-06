#ifndef DISPLAY_H
# define DISPLAY_H

# include "libft_def.h"
# include "geometry.h"
# include "number.h"

typedef struct s_pixel
{
	int		x;
	int		y;
	t_uint	color;
}	t_pixel;

typedef struct s_display
{
	int		w;
	int		h;
	int		w_real;
	int		h_real;
	int		multiplier;
	double	ratio;
	t_color	*colors;
	t_uint	*image;
}	t_display;

t_display		*display_create(int width, int height, int mult);
t_display		*display_destroy(t_display *disp);
void			display_putpixel(t_display *disp, t_pixel p);
int				display_save_bmp(const t_display *disp, const char *path);

#endif
