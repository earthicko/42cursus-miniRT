#include "libft.h"
#include "mlx.h"
#include "number.h"
#include "parser.h"
#include "renderer.h"

void	renderer_destroy(t_renderer *renderer)
{
	if (renderer->scene)
		scene_destroy(renderer->scene);
	if (renderer->disp)
		display_destroy(renderer->disp);
	ft_bzero(renderer, sizeof(t_renderer));
}

// TODO: move hard-coded constants into defines
int	renderer_init(t_renderer *renderer, const char *scene_path)
{
	int	stat;

	ft_bzero(renderer, sizeof(t_renderer));
	renderer->scene = scene_create();
	renderer->disp = display_create(
			DISPLAY_DEFAULT_W, DISPLAY_DEFAULT_H, "miniRT");
	if (!renderer->scene || !renderer->disp)
	{
		renderer_destroy(renderer);
		return (CODE_ERROR_GENERIC);
	}
	renderer->max_depth = 50;
	renderer->n_samples = 1;
	stat = parse_scene(scene_path, renderer->scene);
	if (stat)
	{
		renderer_destroy(renderer);
		return (stat);
	}
	return (CODE_OK);
}

// TODO: define infinity in header
void	renderer_render_ray(t_color	*out,
			t_renderer *renderer, const t_ray *ray, int depth)
{
	t_hit_record		hitrec;
	t_minmax			range;
	t_color				emitted;
	t_scatter_record	scatrec;
	t_color				next_color;

	range.min = DOUBLE_E;
	range.max = 999999999;
	if (depth <= 0)
		return ;
	if (!renderer->scene->world->hit(renderer->scene->world,
			(t_ray*)ray, range, &hitrec))
	{
		vec3_add_vec3_inplace(out, &renderer->scene->bg);
		return ;
	}
	hitrec.material->emit(hitrec.material, &emitted, &hitrec);
	vec3_add_vec3_inplace(out, &emitted);
	if (!hitrec.material->scatter(hitrec.material, &scatrec, ray, &hitrec))
		return ;
	renderer_render_ray(&next_color, renderer, &scatrec.scattered, depth - 1);
	vec3_mult_component_vec3_inplace(&next_color, &scatrec.albedo);
	vec3_add_vec3_inplace(out, &next_color);
}

void	renderer_getpixel(t_renderer *renderer, int x, int y)
{
	t_uv	uv;
	t_ray	ray;

	uv.i[0] = (x + rand_double()) / (renderer->disp->w);
	uv.i[1] = (y + rand_double()) / (renderer->disp->h);
	camera_get_ray_at(&ray, &renderer->scene->cam, &uv);
	renderer_render_ray(renderer->disp->colors + (renderer->disp->w * y) + x,
		renderer, &ray, renderer->max_depth);
}

int	renderer_render(void *param)
{
	t_renderer	*renderer;
	int			x;
	int			y;
	int			n;

	renderer = (t_renderer *)param;
	n = 0;
	while (n < renderer->n_samples)
	{
		y = 0;
		while (y < renderer->disp->h)
		{
			x = 0;
			while (x < renderer->disp->w)
			{
				renderer_getpixel(renderer, x, y);
				x++;
			}
			y++;
		}
		mlx_put_image_to_window(renderer->disp->mlx, renderer->disp->win,
			renderer->disp->img, 0, 0);
		n++;
	}
	return (0);
}
