/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settingman.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGMAN_H
# define SETTINGMAN_H

# include "geometry.h"

# define DISPLAY_TITLE		"Photon Chaser"
# define OUTPUT_FILENAME	"render"
# define LIGHT_DEFAULT_RADIUS		10
# define LIGHT_DEFAULT_INTENSITY	3
# define DISPLAY_DEFAULT_W	500
# define DISPLAY_DEFAULT_H	500
# define DISPLAY_MULTIPLIER	2
# define CAM_DEFAULT_CAMUP_X	0
# define CAM_DEFAULT_CAMUP_Y	1
# define CAM_DEFAULT_CAMUP_Z	0
# define CAM_DEFAULT_FOCALLEN	10
# define RENDERER_MAX_DEPTH			10
# define RENDERER_N_SAMPLES			1000
# define RENDERER_UPDATE_FREQ_SHOW	100
# define RENDERER_UPDATE_FREQ_SAVE	1

#endif
