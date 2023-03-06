/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_interface.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_INTERFACE_H
# define MLX_INTERFACE_H

# include "libft_def.h"
# include "geometry.h"
# include "number.h"

enum	e_appkitkeycode
{
	KEYCODE_ESC = 53,
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
	void	*win;
	void	*img;
	char	*img_addr;
	int		w;
	int		h;
	int		w_real;
	int		h_real;
	int		multiplier;
	double	ratio;
	int		n_pixels;
	t_color	*colors;
}	t_display;

typedef struct s_imgwrapper
{
	char		*filename;
	int			width;
	int			height;
	t_minmax	x_range;
	t_minmax	y_range;
	int			rotation;
	int			flip;
	t_color		*colors;
}	t_imgwrapper;

int				exit_program(void *param);
int				mlx_key_interface(int k, void *param);
void			*mlx_interface_get_mlx_ptr(void);

t_display		*display_create(int width, int height, int mult, char *title);
t_display		*display_destroy(t_display *disp);

void			display_putpixel(t_display *disp, t_pixel p);
void			display_putimage(t_display *disp);

#endif
