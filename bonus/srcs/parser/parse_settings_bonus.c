/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_settings_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft.h"
#include "ptrarr_bonus.h"
#include "msgdef_bonus.h"
#include "print_bonus.h"
#include "defaults_bonus.h"
#include "parser_internal_bonus.h"

static void	set_defaults_display(void)
{
	const int	w = DISPLAY_DEFAULT_W;
	const int	h = DISPLAY_DEFAULT_H;
	const int	m = DISPLAY_MULTIPLIER;

	settingman_display_size(SETTINGMAN_SET, (int *)&w, (int *)&h, (int *)&m);
}

static void	set_defaults_camera(void)
{
	const t_vec3	updir = {
		CAM_DEFAULT_CAMUP_X,
		CAM_DEFAULT_CAMUP_Y,
		CAM_DEFAULT_CAMUP_Z
	};
	const double	focallen = CAM_DEFAULT_FOCALLEN;

	settingman_caminfo(SETTINGMAN_SET, (t_vec3 *)&updir, (double *)&focallen);
}

static void	set_defaults_renderer(void)
{
	const int	values[4] = {
		RENDERER_MAX_DEPTH,
		RENDERER_N_SAMPLES,
		RENDERER_UPDATE_FREQ_SHOW,
		RENDERER_UPDATE_FREQ_SAVE
	};

	settingman_rendererinfo(SETTINGMAN_SET, (int *)values);
}

int	parse_settings(const char *path)
{
	int			i;
	t_ptrarr	*lines;

	set_defaults_display();
	set_defaults_camera();
	set_defaults_renderer();
	lines = read_file_to_strarr(path);
	if (!lines)
		return (CODE_ERROR_IO);
	i = 0;
	while (i < lines->len)
	{
		if (parse_setting_loop(lines->data[i], NULL) == FALSE)
			printf("%s: "MSG_PARSEFAIL"\n", EXEC_NAME, (char *)lines->data[i]);
		i++;
	}
	ptrarr_destroy(lines, destroy_pchar);
	return (CODE_OK);
}
