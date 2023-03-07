/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:56:56 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "settingman.h"
#include "camera.h"
#include "number.h"

void	camera_init_get_h_and_w(const t_camerainfo *info, double *h, double *w)
{
	double	ratio;

	ratio = DISPLAY_DEFAULT_W / DISPLAY_DEFAULT_H;
	*h = 2.0 * tan((info->fov / 2) / (180.0 / M_PI));
	*w = ratio * *h;
}

/*
	w = unit of (cam_start - cam_end)
	u = unit of (cam_up X w)
	v = w X u
*/
void	camera_init_get_uvw(t_camera *cam, const t_camerainfo *info)
{
	t_vec3	view_dir;
	t_vec3	up_dir;

	vec3_sub_vec3(&view_dir, &info->cam_start, &info->cam_end);
	vec3_get_unit(&cam->w, &view_dir);
	vec3_mult_num_inplace(&cam->w,
		(double)DISPLAY_DEFAULT_H / (double)DISPLAY_DEFAULT_W);
	vec3_cross_vec3(&up_dir, &info->cam_up, &cam->w);
	vec3_get_unit(&cam->u, &up_dir);
	vec3_cross_vec3(&cam->v, &cam->w, &cam->u);
	vec3_add_vec3(&cam->uv, &cam->u, &cam->v);
}

/*
	view origin = cam start
	x axis = focal length * width * u
	y axis = focal length * height * v
	pixel origin = view origin - focal length * w - x axis / 2 - y axis / 2
*/
void	camera_init_get_origin_and_axis(
		t_camera *cam, const t_camerainfo *info, double height, double width)
{
	int	i;

	cam->view_origin = info->cam_start;
	vec3_mult_num(&cam->xaxis, &cam->u, CAM_DEFAULT_FOCALLEN * width);
	vec3_mult_num(&cam->yaxis, &cam->v, CAM_DEFAULT_FOCALLEN * height);
	i = 0;
	while (i < 3)
	{
		cam->pixel_origin.i[i]
			= cam->view_origin.i[i]
			- CAM_DEFAULT_FOCALLEN * cam->w.i[i]
			- cam->xaxis.i[i] / 2
			- cam->yaxis.i[i] / 2;
		i++;
	}
}

void	camera_init(t_camera *cam, const t_camerainfo *info)
{
	double	height;
	double	width;

	cam->pixel_w = DISPLAY_DEFAULT_W;
	cam->pixel_h = DISPLAY_DEFAULT_H;
	camera_init_get_h_and_w(info, &height, &width);
	camera_init_get_uvw(cam, info);
	camera_init_get_origin_and_axis(cam, info, height, width);
}