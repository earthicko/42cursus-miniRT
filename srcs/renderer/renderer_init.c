#include <stdio.h>
#include "libft.h"
#include "renderer.h"
#include "parser.h"

void	renderer_destroy(t_renderer *renderer)
{
	if (renderer->scene)
		scene_destroy(renderer->scene);
	if (renderer->disp)
		display_destroy(renderer->disp);
	ft_bzero(renderer, sizeof(t_renderer));
}

int	renderer_init(t_renderer *renderer, const char *scene_path)
{
	int	stat;

	ft_bzero(renderer, sizeof(t_renderer));
	renderer->scene = scene_create();
	renderer->disp = display_create(
			DISPLAY_DEFAULT_W, DISPLAY_DEFAULT_H, DISPLAY_TITLE);
	if (!renderer->scene || !renderer->disp)
	{
		renderer_destroy(renderer);
		return (CODE_ERROR_GENERIC);
	}
	renderer->max_depth = RENDERER_MAX_DEPTH;
	renderer->n_samples = RENDERER_N_SAMPLES;
	stat = parse_scene(scene_path, renderer->scene);
	if (stat)
	{
		renderer_destroy(renderer);
		return (stat);
	}
	return (CODE_OK);
}
