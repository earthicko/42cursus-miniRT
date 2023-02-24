#include "camera.h"
#include "ray.h"

/*
	ray origin = view origin + uv
	ray dir = pixel origin + (x * x axis + y * y axis) - ray origin
*/
void	camera_get_ray_at(t_ray *out, const t_camera *cam, double x, double y)
{
	int	i;

	out->orig = cam->view_origin;
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
