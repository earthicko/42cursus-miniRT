#ifndef MLX_INTERFACE_H
# define MLX_INTERFACE_H

# include "libft_def.h"

# define DISPLAY_DEFAULT_W	400
# define DISPLAY_DEFAULT_H	300

enum	e_appkitkeycode
{
	KEYCODE_ESC = 53,
	KEYCODE_Q = 12,
	KEYCODE_W = 13,
	KEYCODE_E = 14,
	KEYCODE_A = 0,
	KEYCODE_S = 1,
	KEYCODE_D = 2,
	KEYCODE_I = 34,
	KEYCODE_J = 38,
	KEYCODE_K = 40,
	KEYCODE_L = 37,
	KEYCODE_SP = 49,
	KEYCODE_PLUS = 69,
	KEYCODE_MINUS = 78
};

enum	e_appkitevent
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

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
