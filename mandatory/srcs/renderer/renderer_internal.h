#ifndef RENDERER_INTERNAL_H
# define RENDERER_INTERNAL_H

# include "settingman.h"
# include "renderer.h"

void	renderer_render_pixel(t_renderer *renderer, int x, int y);
void	renderer_write_color(t_renderer *renderer, int n_samples);
void	renderer_render_loop(t_renderer *renderer);

char	*get_filename(int n);
void	renderer_render_showstat(int n_samples);

#endif
