#include <stdio.h>
#include "libft.h"
#include "renderer.h"
#include "msgdef.h"
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
	ft_print_error(EXEC_NAME, stat);
	return (stat);
}

static void	set_rendererinfo(t_renderer *renderer, int displayval[3])
{
	int	values[4];

	settingman_display_size(SETTINGMAN_GET,
		&displayval[0], &displayval[1], &displayval[2]);
	settingman_rendererinfo(SETTINGMAN_GET, values);
	renderer->max_depth = values[0];
	renderer->max_samples = values[1];
	renderer->freq_update = values[2];
	renderer->freq_save = values[3];
}

int	renderer_init(t_renderer *renderer, const char *path)
{
	int	displayval[3];
	int	stat;

	ft_bzero(renderer, sizeof(t_renderer));
	renderer->scene = scene_create();
	if (!renderer->scene)
		return (abort_renderer_init(renderer, CODE_ERROR_GENERIC));
	parse_settings(SETTING_FILENAME);
	stat = parse_scene(path, renderer->scene);
	if (stat)
		return (abort_renderer_init(renderer, stat));
	set_rendererinfo(renderer, displayval);
	if (displayval[1] < RENDER_WORKER_N)
		return (abort_renderer_init(renderer, CODE_ERROR_DATA));
	renderer->disp = display_create(
			displayval[0], displayval[1], displayval[2], DISPLAY_TITLE);
	if (!renderer->disp)
		return (abort_renderer_init(renderer, CODE_ERROR_GENERIC));
	return (CODE_OK);
}
