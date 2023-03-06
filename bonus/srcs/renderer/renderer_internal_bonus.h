/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_internal_bonus.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_INTERNAL_BONUS_H
# define RENDERER_INTERNAL_BONUS_H

# include "settingman_bonus.h"
# include "renderer_bonus.h"

void	renderer_render_pixel(t_renderer *renderer, int x, int y);
void	renderer_write_color(t_renderer *renderer, int n_samples);
void	renderer_render_loop_multithread(t_renderer_worker *worker);
void	renderer_render_loop(t_renderer *renderer);

char	*get_filename(int n);
void	renderer_render_showstat(int n_samples);
void	renderer_render_showstat_multithread(int n_samples, int worker_idx);
int		get_next_milestone(t_renderer *renderer, int current_milestone);

void	*worker_routine(void *arg);
int		init_workers(t_renderer *renderer, t_renderer_supervisor *stat);
void	terminate_workers(t_renderer_supervisor *stat);

t_bool	is_render_finished(t_renderer_supervisor *stat);
int		n_samples_main(t_renderer_supervisor *stat);
int		n_samples_worker(t_renderer_supervisor *stat, int i);
int		milestone(t_renderer_supervisor *stat);
t_bool	all_workers_reach_milestone(t_renderer_supervisor *stat);

void	set_render_finished(t_renderer_supervisor *stat);
void	set_milestone(t_renderer_supervisor *stat, int milestone);
void	set_n_samples_main(t_renderer_supervisor *stat, int n_samples);
void	set_n_samples_worker(t_renderer_supervisor *stat, int i, int n_samples);

#endif
