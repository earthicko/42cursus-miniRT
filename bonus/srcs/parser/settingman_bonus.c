#include "libft.h"
#include "settingman_bonus.h"

void	settingman_display_size(int mode,
			int *w_buf, int *h_buf, int *multiplier_buf)
{
	static int	w;
	static int	h;
	static int	multiplier;

	if (mode == SETTINGMAN_GET)
	{
		if (w_buf)
			*w_buf = w;
		if (h_buf)
			*h_buf = h;
		if (multiplier_buf)
			*multiplier_buf = multiplier;
	}
	if (mode == SETTINGMAN_SET)
	{
		if (w_buf)
			w = *w_buf;
		if (h_buf)
			h = *h_buf;
		if (multiplier_buf)
			multiplier = *multiplier_buf;
	}
}

void	settingman_caminfo(int mode,
			t_vec3 *camdir_buf, double *focallen_buf)
{
	static t_vec3	camdir;
	static double	focallen;

	if (mode == SETTINGMAN_GET)
	{
		if (camdir_buf)
			ft_memcpy(camdir_buf, &camdir, sizeof(t_vec3));
		if (focallen_buf)
			*focallen_buf = focallen;
	}
	if (mode == SETTINGMAN_SET)
	{
		if (camdir_buf)
			ft_memcpy(&camdir, camdir_buf, sizeof(t_vec3));
		if (focallen_buf)
			focallen = *focallen_buf;
	}
}

// sets max_depth, n_samples, update frequency (show), update frequency (save)
void	settingman_rendererinfo(int mode, int buf[4])
{
	static int	max_depth;
	static int	n_samples;
	static int	update_freq_show;
	static int	update_freq_save;

	if (mode == SETTINGMAN_GET)
	{
		buf[0] = max_depth;
		buf[1] = n_samples;
		buf[2] = update_freq_show;
		buf[3] = update_freq_save;
	}
	if (mode == SETTINGMAN_SET)
	{
		max_depth = buf[0];
		n_samples = buf[1];
		update_freq_show = buf[2];
		update_freq_save = buf[3];
	}
}
