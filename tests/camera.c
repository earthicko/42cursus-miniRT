#include <stdio.h>
#include "number.h"
#include "camera.h"
#include "print.h"

void	set_caminfo(t_camerainfo *caminfo)
{
	vec3_setval(&caminfo->cam_start, 0, 0, 12);
	vec3_setval(&caminfo->cam_end, 0, 0, 0);
	vec3_setval(&caminfo->cam_up, 0, 1, 0);
	caminfo->fov = 20;
	caminfo->pixel_w = 400;
	caminfo->pixel_h = 300;
	caminfo->focallen = 10.0;
	printf("Cam start ");
	print_vec3(&caminfo->cam_start);
	printf(", Cam end ");
	print_vec3(&caminfo->cam_end);
	printf(", Cam up ");
	print_vec3(&caminfo->cam_up);
	printf(", fov %.2f, pixel (%d x %d), focallen %.2f\n",
		caminfo->fov,
		caminfo->pixel_w,
		caminfo->pixel_h,
		caminfo->focallen);
}

void	test_get_ray(t_camera *cam, int x, int y)
{
	double	u;
	double	v;
	t_ray	ray;

	u = (x + rand_double_ts()) / (cam->pixel_w - 1);
	v = (y + rand_double_ts()) / (cam->pixel_h - 1);
	printf("for pixel (%d, %d) uv=(%.2f, %.2f) ", x, y, u, v);
	camera_get_ray_at(&ray, cam, u, v);
	print_ray(&ray);
	printf("\n");
}

void	loop_cam(t_camera *cam, int nsamples)
{
	int	x;
	int	y;
	int	s;

	(void)cam;
	y = cam->pixel_h - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < cam->pixel_w)
		{
			s = 0;
			while (s < nsamples)
			{
				printf("for pixel (%d, %d)\n", x, y);
				s++;
			}
			x++;
		}
		y--;
	}
}

void	test_cam(t_camera *cam)
{
	int	nsamples;

	nsamples = 2;
	test_get_ray(cam, 50, 100);
	test_get_ray(cam, 150, 100);
	test_get_ray(cam, 250, 100);
	test_get_ray(cam, 0, 150);
	test_get_ray(cam, 200, 150);
	test_get_ray(cam, 400, 150);
	test_get_ray(cam, 400, 300);
}

/*
typedef struct s_camerainfo
{
	t_point	cam_start;
	t_point	cam_end;
	t_vec3	cam_up;
	double	fov;
	double	w_to_h;
	double	focallen;
}	t_camerainfo;
*/
int	main(void)
{
	t_camerainfo	caminfo;
	t_camera		cam;

	set_caminfo(&caminfo);
	camera_init(&cam, &caminfo);
	print_camera(&cam);
	printf("\n");
	test_cam(&cam);
	return (0);
}
