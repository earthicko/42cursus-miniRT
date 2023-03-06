#ifndef RENDERER_H
# define RENDERER_H

# include <pthread.h>
# include "settingman.h"
# include "mlx_interface.h"
# include "scene.h"

typedef pthread_t						t_thread;
typedef pthread_mutex_t					t_mutex;
typedef struct s_renderer				t_renderer;

typedef struct s_renderer
{
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

int		renderer_init(t_renderer *renderer, const char *path);
void	renderer_destroy(t_renderer *renderer);
int		renderer_render(void *param);
int		renderer_render_multithreaded(void *param);

#endif
