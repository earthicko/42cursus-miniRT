/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "ptrarr.h"
# include "camera.h"
# include "hittable.h"

typedef struct s_resources
{
	t_ptrarr	*primitives;
	t_ptrarr	*materials;
	t_ptrarr	*textures;
}	t_resources;

typedef struct s_scene
{
	t_resources	res;
	t_camera	cam;
	t_hittable	*world;
	t_hittable	*objects;
	t_color		bg;
}	t_scene;

t_scene		*scene_create(void);
void		scene_destroy(t_scene *scene);

#endif
