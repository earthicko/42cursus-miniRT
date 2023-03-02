#ifndef SETTINGMAN_H
# define SETTINGMAN_H

# include "geometry.h"

# define DISPLAY_TITLE		"Photon Stalkers"
# define OUTPUT_FILENAME	"render"
# define SETTING_FILENAME	"./settings.rt"
# define LIGHT_DEFAULT_RADIUS		10
# define LIGHT_DEFAULT_INTENSITY	3

enum e_settingmanmode
{
	GET = 0,
	SET
};

void	settingman_display_size(int mode,
			int *w_buf, int *h_buf, int *multiplier_buf);
void	settingman_caminfo(int mode,
			t_vec3 *camdir_buf, double *focallen_buf);
void	settingman_rendererinfo(int mode,
			int buf[4]);

#endif