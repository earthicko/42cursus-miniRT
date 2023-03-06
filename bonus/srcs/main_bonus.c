#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "mlx.h"
#include "mlx_interface_bonus.h"
#include "parser_bonus.h"
#include "msgdef_bonus.h"
#include "scene_bonus.h"
#include "renderer_bonus.h"

static t_bool	match_extension(const char *path, const char *ext)
{
	size_t	start;

	start = ft_strlen(path) - ft_strlen(ext);
	if (ft_strncmp(path + start, ext, ft_strlen(ext) + 1) == 0)
		return (TRUE);
	return (FALSE);
}

static void	init_textures(t_ptrarr *textures)
{
	int				i;
	t_texture		*tx;
	t_color			out;
	t_hit_record	rec;

	i = 0;
	while (i < textures->len)
	{
		tx = (t_texture *)ptrarr_get(textures, i);
		tx->get_color_at(tx, &out, &rec);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_renderer	renderer;
	void		*mlx;

	if (argc != 2 || !match_extension(argv[1], ".rt"))
	{
		printf("Error\n");
		printf(MSG_USAGE"\n");
		return (2);
	}
	if (renderer_init(&renderer, argv[1]))
		return (1);
	init_textures(renderer.scene->res.textures);
	mlx_hook(renderer.disp->win, ON_KEYDOWN, 0, mlx_key_interface, &renderer);
	mlx_hook(renderer.disp->win, ON_DESTROY, 0, exit_program, &renderer);
	mlx = mlx_interface_get_mlx_ptr();
	if (RENDER_WORKER_N == 1)
		mlx_loop_hook(mlx, renderer_render, &renderer);
	else
		mlx_loop_hook(mlx, renderer_render_multithreaded, &renderer);
	mlx_loop(mlx);
	return (0);
}
