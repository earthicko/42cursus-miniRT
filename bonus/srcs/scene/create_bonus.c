/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ptrarr_bonus.h"
#include "hittable_bonus.h"
#include "scene_bonus.h"

static t_bool	is_all_allocated(t_scene *scene)
{
	if (!(scene->res.primitives))
		return (FALSE);
	if (!(scene->res.materials))
		return (FALSE);
	if (!(scene->res.textures))
		return (FALSE);
	if (!(scene->world))
		return (FALSE);
	if (!(scene->objects))
		return (FALSE);
	return (TRUE);
}

t_scene	*scene_create(void)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
	ft_bzero(scene, sizeof(t_scene));
	scene->res.primitives = ptrarr_create();
	scene->res.materials = ptrarr_create();
	scene->res.textures = ptrarr_create();
	scene->world = hittable_list_create();
	scene->objects = hittable_list_create();
	if (!is_all_allocated(scene))
	{
		scene_destroy(scene);
		return (NULL);
	}
	return (scene);
}