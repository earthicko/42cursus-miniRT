/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settingman_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGMAN_BONUS_H
# define SETTINGMAN_BONUS_H

# include "geometry_bonus.h"

# define DISPLAY_TITLE		"Photon Chaser"
# define RENDER_WORKER_N		6
# define RENDER_SYNC_INTERVAL	1
# define OUTPUT_FILENAME	"render"
# define SETTING_FILENAME	"./settings.rt"
# define LIGHT_DEFAULT_RADIUS		10
# define LIGHT_DEFAULT_INTENSITY	3

enum e_settingmanmode
{
	SETTINGMAN_GET = 0,
	SETTINGMAN_SET
};

void	settingman_display_size(int mode,
			int *w_buf, int *h_buf, int *multiplier_buf);
void	settingman_caminfo(int mode,
			t_vec3 *camdir_buf, double *focallen_buf);
void	settingman_rendererinfo(int mode,
			int buf[4]);

#endif
