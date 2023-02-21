#ifndef CAMERA_H
# define CAMERA_H

# include "geometry.h"
# include "ray.h"

typedef struct s_camerainfo
{
	t_point	cam_start;
	t_point	cam_end;
	t_vec3	cam_up;
	double	fov;
	double	w_to_h;
	double	focallen;
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
}	t_camera;

void	camera_init(t_camera *cam, t_camerainfo *caminfo);
void	camera_get_ray_at(t_ray *out, t_camera *cam, double x, double y);

#endif
