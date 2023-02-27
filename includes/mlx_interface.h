#ifndef MLX_INTERFACE_H
# define MLX_INTERFACE_H

# include "libft_def.h"
# include "geometry.h"
# include "settings.h"

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
	int		w_real;
	int		h_real;
	double	ratio;
	int		n_pixels;
	t_color	*colors;
}	t_display;

int			exit_program(void *param);
int			mlx_key_interface(int k, void *param);

t_display	*display_create(int width, int height, char *title);
t_display	*display_destroy(t_display *disp);

void		display_putpixel(t_display *disp, t_pixel p);
void		display_putimage(t_display *disp);

int			display_save_bmp(const t_display *disp, const char *path);

#endif
