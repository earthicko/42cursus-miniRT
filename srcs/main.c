#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "mlx.h"
#include "mlx_interface.h"
#include "parser.h"
#include "msgdef.h"
#include "scene.h"

int	exit_program(void *param)
{
	scene_destroy((t_scene *)param);
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
	t_display	*disp;
	t_scene		*scene;

	if (argc != 2 || !match_extension(argv[1], ".rt"))
	{
		printf(MSG_USAGE"\n");
		return (2);
	}
	scene = scene_create();
	if (!scene)
		return (1);
	if (parse_scene(argv[1], scene))
	{
		scene_destroy(scene);
		return (1);
	}
	disp = display_create(DISPLAY_DEFAULT_W, DISPLAY_DEFAULT_H, "miniRT");
	mlx_hook(disp->win, ON_DESTROY, 0, exit_program, scene);
	mlx_loop(disp->mlx);
	return (0);
}
