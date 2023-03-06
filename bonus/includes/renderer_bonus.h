#ifndef RENDERER_BONUS_H
# define RENDERER_BONUS_H

# include <pthread.h>
# include "settingman_bonus.h"
# include "mlx_interface_bonus.h"
# include "scene_bonus.h"

typedef pthread_t						t_thread;
typedef pthread_mutex_t					t_mutex;
typedef struct s_renderer				t_renderer;
typedef struct s_renderer_supervisor	t_renderer_supervisor;

typedef struct s_renderer_worker
{
	t_renderer				*renderer;
	t_renderer_supervisor	*super;
	int						n_samples;
	t_mutex					m_n_samples;
	int						y_begin;
	int						y_end;
}	t_renderer_worker;

typedef struct s_renderer_supervisor
{
	t_bool				finished;
	t_mutex				m_finished;
	int					n_samples;
	t_mutex				m_n_samples;
	int					milestone;
	t_mutex				m_milestone;
	t_thread			ids[RENDER_WORKER_N];
	t_renderer_worker	workers[RENDER_WORKER_N];
}	t_renderer_supervisor;

typedef struct s_renderer
{
	int						max_samples;
	int						max_depth;
	int						freq_update;
	int						freq_save;
	t_display				*disp;
	t_scene					*scene;
	t_renderer_supervisor	*stat;
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

void	terminate_workers(t_renderer_supervisor *stat);

#endif
