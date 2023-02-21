#include "camera.h"
#include "ray.h"

/*
	ray origin = view origin + uv
	ray dir = pixel origin + (x * x axis + y * y axis) - ray origin
*/
void	camera_get_ray_at(t_ray *out, t_camera *cam, double x, double y)
{
	int	i;

	vec3_add_vec3(&out->orig, &cam->view_origin, &cam->uv);
	i = 0;
	while (i < 3)
	{
		out->dir.i[i]
			= cam->pixel_origin.i[i]
			+ x * cam->xaxis.i[i]
			+ y * cam->yaxis.i[i]
			- out->orig.i[i];
		i++;
	}
}
