#include "libft.h"
#include "mlx.h"
#include "number.h"
#include "parser.h"
#include "renderer.h"

void	renderer_render_ray(t_color	*out,
			t_renderer *renderer, const t_ray *ray, int depth)
{
	t_hit_record		hitrec;
	t_minmax			range;
	t_color				emitted;
	t_scatter_record	scatrec;
	t_color				next_color;

	range.min = DOUBLE_E;
	range.max = DOUBLE_INF;
	if (depth <= 0)
	{
		vec3_setval(out, 0, 0, 0);
		return ;
	}
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

static void	map_pixel_color(int *rgb, t_renderer *renderer, t_pixel *p, int n)
{
	const t_minmax	in = {0, n + 1};
	const t_minmax	out = {0, 255};
	int				i;

	i = 0;
	while (i < 3)
	{
		rgb[i] = map_minmax(renderer->disp->colors[
				(renderer->disp->w * (renderer->disp->h - p->y))
				+ p->x].i[i], &in, &out);
		rgb[i] = clamp_int(rgb[i], 0, 255);
		i++;
	}
}

// TODO: gamma correction, NaN filtering
void	renderer_write_color(t_renderer *renderer, int n_samples)
{
	t_pixel			p;
	int				rgb[3];

	p.y = 0;
	while (p.y < renderer->disp->h)
	{
		p.x = 0;
		while (p.x < renderer->disp->w)
		{
			map_pixel_color(rgb, renderer, &p, n_samples);
			p.color = rgb[0] << 16 | rgb[1] << 8 | rgb[2];
			display_putpixel(renderer->disp, p);
			p.x++;
		}
		p.y++;
	}
}

int	renderer_render(void *param)
{
	t_renderer	*renderer;
	int			x;
	int			y;
	static int	n_samples_so_far;

	renderer = (t_renderer *)param;
	if (n_samples_so_far >= renderer->n_samples)
		return (0);
	printf("Sample %d\n", n_samples_so_far);
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
	renderer_write_color(renderer, n_samples_so_far);
		mlx_put_image_to_window(renderer->disp->mlx, renderer->disp->win,
			renderer->disp->img, 0, 0);
	n_samples_so_far++;
	return (0);
}
