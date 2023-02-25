#ifndef MLX_INTERFACE_H
# define MLX_INTERFACE_H

# include "libft_def.h"

# define DISPLAY_DEFAULT_W	400
# define DISPLAY_DEFAULT_H	300

typedef struct s_pixel
{
	int		x;
	int		y;
	t_uint	color;
}	t_pixel;

typedef struct s_display
{
	int		bpp;
	int		nbytes;
	int		endian;
	void	*mlx;
	void	*win;
	void	*img;
	char	*img_addr;
	int		w;
	int		h;
	double	ratio;
	int		n_v;
	t_pixel	*v;
}	t_display;

t_display	*display_create(int width, int height, char *title);
t_display	*display_destroy(t_display *disp);

int			display_start_buffer(t_display *disp);
int			display_end_buffer(t_display *disp);
void		display_putpixel(t_display *disp, t_pixel p);

#endif
