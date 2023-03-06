#include <stdio.h>
#include "libft.h"
#include "renderer.h"
#include "parser.h"
#include "settingman.h"

void	renderer_destroy(t_renderer *renderer)
{
	if (renderer->scene)
		scene_destroy(renderer->scene);
	if (renderer->disp)
		display_destroy(renderer->disp);
	ft_bzero(renderer, sizeof(t_renderer));
}

static int	abort_renderer_init(t_renderer *renderer, int stat)
{
	renderer_destroy(renderer);
	return (stat);
}

int	renderer_init(t_renderer *renderer, const char *path)
{
	int	stat;

	ft_bzero(renderer, sizeof(t_renderer));
	renderer->scene = scene_create();
	if (!renderer->scene)
		return (abort_renderer_init(renderer, CODE_ERROR_GENERIC));
	stat = parse_scene(path, renderer->scene);
	if (stat)
		return (abort_renderer_init(renderer, stat));
	renderer->disp = display_create(DISPLAY_DEFAULT_W, DISPLAY_DEFAULT_H,
			DISPLAY_MULTIPLIER, DISPLAY_TITLE);
	if (!renderer->disp)
		return (abort_renderer_init(renderer, CODE_ERROR_GENERIC));
	return (CODE_OK);
}
