#include <math.h>
#include "camera.h"
#include "number.h"

void	camera_init_get_h_and_w(const t_camerainfo *info, double *h, double *w)
{
	double	w_to_h;

	w_to_h = info->pixel_w / info->pixel_h;
	*h = 2.0 * tan(deg_to_rad(info->fov / 2));
	*w = w_to_h * *h;
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
		(double)info->pixel_h / (double)info->pixel_w);
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
	vec3_mult_num(&cam->xaxis, &cam->u, info->focallen * width);
	vec3_mult_num(&cam->yaxis, &cam->v, info->focallen * height);
	i = 0;
	while (i < 3)
	{
		cam->pixel_origin.i[i]
			= cam->view_origin.i[i]
			- info->focallen * cam->w.i[i]
			- cam->xaxis.i[i] / 2
			- cam->yaxis.i[i] / 2;
		i++;
	}
}

void	camera_init(t_camera *cam, const t_camerainfo *info)
{
	double	height;
	double	width;

	cam->pixel_w = info->pixel_w;
	cam->pixel_h = info->pixel_h;
	camera_init_get_h_and_w(info, &height, &width);
	camera_init_get_uvw(cam, info);
	camera_init_get_origin_and_axis(cam, info, height, width);
}
