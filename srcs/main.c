#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "mlx.h"
#include "mlx_interface.h"
#include "parser.h"
#include "msgdef.h"
#include "scene.h"
#include "renderer.h"

int	exit_program(void *param)
{
	renderer_destroy((t_renderer *)param);
	system("leaks miniRT");
	exit(0);
}

t_bool	match_extension(const char *path, const char *ext)
{
	size_t	start;

	start = ft_strlen(path) - ft_strlen(ext);
	if (ft_strncmp(path + start, ext, ft_strlen(ext) + 1) == 0)
		return (TRUE);
	return (FALSE);
}

int	main(int argc, char **argv)
{
	t_renderer	renderer;

	if (argc != 2 || !match_extension(argv[1], ".rt"))
	{
		printf(MSG_USAGE"\n");
		return (2);
	}
	if (renderer_init(&renderer, argv[1]))
		return (1);
	mlx_hook(renderer.disp->win, ON_DESTROY, 0, exit_program, &renderer);
	mlx_loop_hook(renderer.disp->mlx, renderer_render, &renderer);
	mlx_loop(renderer.disp->mlx);
	return (0);
}
