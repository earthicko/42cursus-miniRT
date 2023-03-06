#include <stdio.h>
#include "libft.h"
#include "mlx.h"
#include "number.h"
#include "parser.h"
#include "print.h"
#include "renderer.h"

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
		vec3_add_vec3_inplace(out, &renderer->scene->bg);
		return ;
	}
	hitrec.material->emit(hitrec.material, &info.emitted, &hitrec);
	vec3_add_vec3_inplace(out, &info.emitted);
	if (!hitrec.material->scatter(hitrec.material, &scatrec, ray, &hitrec))
		return ;
	renderer_render_ray(&info.next_color,
		renderer, &scatrec.scattered, depth - 1);
	vec3_mult_component_vec3_inplace(&info.next_color, &scatrec.albedo);
	vec3_add_vec3_inplace(out, &info.next_color);
}

void	renderer_render_pixel(t_renderer *renderer, int x, int y)
{
	t_uv	uv;
	t_ray	ray;

	uv.i[0] = (x + rand_double_ts()) / (renderer->disp->w);
	uv.i[1] = (y + rand_double_ts()) / (renderer->disp->h);
	camera_get_ray_at(&ray, &renderer->scene->cam, &uv);
	renderer_render_ray(renderer->disp->colors + (renderer->disp->w * y) + x,
		renderer, &ray, renderer->max_depth);
}
