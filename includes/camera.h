#ifndef CAMERA_H
# define CAMERA_H

# include "geometry.h"
# include "ray.h"

# define CAM_DEFAULT_CAMUP_X	0
# define CAM_DEFAULT_CAMUP_Y	1
# define CAM_DEFAULT_CAMUP_Z	0
# define CAM_DEFAULT_FOCALLEN	10
# define CAM_DEFAULT_PIXEL_W	400
# define CAM_DEFAULT_PIXEL_H	300

typedef struct s_camerainfo
{
	t_point	cam_start;
	t_point	cam_end;
	t_vec3	cam_up;
	double	fov;
	double	focallen;
	int		pixel_w;
	int		pixel_h;
}	t_camerainfo;

typedef struct s_camera
{
	t_point	view_origin;
	t_point	pixel_origin;
	t_vec3	xaxis;
	t_vec3	yaxis;
	t_vec3	u;
	t_vec3	v;
	t_vec3	w;
	t_vec3	uv;
	int		pixel_w;
	int		pixel_h;
}	t_camera;

void	camera_init(t_camera *cam, const t_camerainfo *caminfo);
void	camera_get_ray_at(t_ray *out, const t_camera *cam, double x, double y);

#endif
