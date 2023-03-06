#include <stdio.h>
#include "hittable.h"
#include "ray.h"
#include "camera.h"
#include "print.h"

void	print_vec2(const t_vec2 *vec2)
{
	printf("(%.2f, %.2f)", vec2->i[0], vec2->i[1]);
}

void	print_vec3(const t_vec3 *vec3)
{
	printf("(%.2f, %.2f, %.2f)", vec3->i[0], vec3->i[1], vec3->i[2]);
}

void	print_ray(const t_ray *ray)
{
	printf("Ray ");
	print_vec3(&ray->orig);
	printf(" -> ");
	print_vec3(&ray->dir);
}

void	print_camera(const t_camera *cam)
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

void	print_mtx44(const t_mtx44 *mtx44)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		printf("| %.2f %.2f %.2f %.2f |\n",
			mtx44->i[i][0],
			mtx44->i[i][1],
			mtx44->i[i][2],
			mtx44->i[i][3]);
		i++;
	}
}
