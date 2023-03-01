#ifndef SETTINGMAN_H
# define SETTINGMAN_H

# include "geometry.h"

// TODO: delete defines when settingman utilization is complete
# define DISPLAY_DEFAULT_W	25
# define DISPLAY_DEFAULT_H	25
# define DISPLAY_MULTIPLIER	20
# define DISPLAY_TITLE		"Photon Stalkers"
# define OUTPUT_FILENAME	"render"
# define CAM_DEFAULT_CAMUP_X	0
# define CAM_DEFAULT_CAMUP_Y	1
# define CAM_DEFAULT_CAMUP_Z	0
# define CAM_DEFAULT_FOCALLEN	10
# define RENDERER_MAX_DEPTH			10
# define RENDERER_N_SAMPLES			1
# define RENDERER_UPDATE_FREQ_SHOW	10
# define RENDERER_UPDATE_FREQ_SAVE	1000000000
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
