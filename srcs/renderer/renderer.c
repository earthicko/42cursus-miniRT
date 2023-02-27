#include <stdio.h>
#include "libft.h"
#include "mlx.h"
#include "number.h"
#include "parser.h"
#include "print.h"
#include "renderer.h"

void	renderer_write_color(t_renderer *renderer, int n_samples);

static void	init_renderer_render_ray(
		t_renderer *renderer, t_renderinfo *info, int depth)
{
	vec3_setval(&info->next_color, 0, 0, 0);
	info->range.min = DOUBLE_E;
	info->range.max = DOUBLE_INF;
	if (depth == renderer->max_depth)
		info->target = renderer->scene->objects;
	else
		info->target = renderer->scene->world;
}

void	renderer_render_ray(t_color	*out,
			t_renderer *renderer, const t_ray *ray, int depth)
{
	t_hit_record		hitrec;
	t_scatter_record	scatrec;
	t_renderinfo		info;

	init_renderer_render_ray(renderer, &info, depth);
	if (depth <= 0)
	{
		vec3_setval(out, 0, 0, 0);
		return ;
	}
	if (!info.target->hit(info.target, ray, info.range, &hitrec))
	{
		// printf(" return bg ");
		vec3_add_vec3_inplace(out, &renderer->scene->bg);
		return ;
	}
	// printf("depth %d ", depth);
	// print_hit_record(&hitrec);
	// printf(" ");
	hitrec.material->emit(hitrec.material, &info.emitted, &hitrec);
	vec3_add_vec3_inplace(out, &info.emitted);
	// printf("emit ");
	// print_vec3(&info.emitted);
	// printf(" ");
	if (!hitrec.material->scatter(hitrec.material, &scatrec, ray, &hitrec))
		return ;
	// print_scatter_record(&scatrec);
	// printf(" ");
	renderer_render_ray(&info.next_color,
		renderer, &scatrec.scattered, depth - 1);
	// printf(" got color ");
	// print_vec3(&info.next_color);
	vec3_mult_component_vec3_inplace(&info.next_color, &scatrec.albedo);
	vec3_add_vec3_inplace(out, &info.next_color);
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
	// printf("Pixel color at (%d, %d) is ", x, y);
	// print_vec3(renderer->disp->colors + (renderer->disp->w * y) + x);
	// printf("\n");
}

static void	renderer_render_loop(t_renderer *renderer, int n_samples_so_far)
{
	int					x;
	int					y;
	static int			i;
	const static char	*blinker[3] = {".     ", "..    ", "...   "};

	if (n_samples_so_far == renderer->n_samples
		|| n_samples_so_far % RENDERER_UPDATE_FREQ == 0)
	{
		ft_printf("\rSample count %d ", n_samples_so_far);
		ft_printf("%s", blinker[(i++) % (sizeof(blinker) / sizeof(char *))]);
	}
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
}

int	renderer_render(void *param)
{
	t_renderer	*renderer;
	static int	n_samples_so_far;
	static int	render_finished;

	renderer = (t_renderer *)param;
	if (n_samples_so_far >= renderer->n_samples)
	{
		if (!render_finished)
		{
			printf("\nRender finished.\n");
			render_finished = 1;
			mlx_put_image_to_window(renderer->disp->mlx, renderer->disp->win,
				renderer->disp->img, 0, 0);
		}
		return (0);
	}
	renderer_render_loop(renderer, n_samples_so_far);
	if (n_samples_so_far % RENDERER_UPDATE_FREQ == 0)
	{
		renderer_write_color(renderer, n_samples_so_far);
		mlx_put_image_to_window(renderer->disp->mlx, renderer->disp->win,
			renderer->disp->img, 0, 0);
	}
	n_samples_so_far++;
	return (0);
}
