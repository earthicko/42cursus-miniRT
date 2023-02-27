#ifndef RENDERER_H
# define RENDERER_H

# include "mlx_interface.h"
# include "scene.h"

typedef struct s_renderer
{
	int			n_samples;
	int			max_depth;
	t_display	*disp;
	t_scene		*scene;
}	t_renderer;

typedef struct s_renderinfo
{
	t_minmax	range;
	t_color		emitted;
	t_color		next_color;
	t_hittable	*target;
}	t_renderinfo;

int		renderer_init(t_renderer *renderer, const char *scene_path);
void	renderer_destroy(t_renderer *renderer);
int		renderer_render(void *param);

#endif
