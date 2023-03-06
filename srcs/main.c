#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "display.h"
#include "parser.h"
#include "msgdef.h"
#include "scene.h"
#include "renderer.h"

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

static void	render_until_done(int (*routine)(void *), void *arg)
{
	while (TRUE)
	{
		if (routine(arg))
			break ;
	}
}

int	main(int argc, char **argv)
{
	t_renderer	renderer;

	if (argc != 2 || !match_extension(argv[1], ".rt"))
	{
		printf("Error\n");
		printf(MSG_USAGE"\n");
		return (2);
	}
	if (renderer_init(&renderer, argv[1]))
		return (1);
	init_textures(renderer.scene->res.textures);
	if (RENDER_WORKER_N == 1)
		render_until_done(renderer_render, &renderer);
	else
		render_until_done(renderer_render_multithreaded, &renderer);
	return (0);
}
