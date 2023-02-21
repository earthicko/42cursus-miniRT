#include <stdio.h>
#include "ray.h"
#include "camera.h"
#include "print.h"

void	print_vec3(t_vec3 *vec3)
{
	printf("(%.2f, %.2f, %.2f)", vec3->i[0], vec3->i[1], vec3->i[2]);
}

void	print_ray(t_ray *ray)
{
	printf("Ray ");
	print_vec3(&ray->orig);
	printf(" -> ");
	print_vec3(&ray->dir);
}

/*
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
*/
void	print_camera(t_camera *cam)
{
	printf("Camera orig: ");
	print_vec3(&cam->view_origin);
	printf(" pixel orig: ");
	print_vec3(&cam->pixel_origin);
	printf(" x axis: ");
	print_vec3(&cam->xaxis);
	printf(" y axis: ");
	print_vec3(&cam->yaxis);
	printf(" u: ");
	print_vec3(&cam->u);
	printf(" v: ");
	print_vec3(&cam->v);
	printf(" w: ");
	print_vec3(&cam->w);
	printf(" uv: ");
	print_vec3(&cam->uv);
}
