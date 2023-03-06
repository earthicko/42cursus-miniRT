/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_bonus.c                                    :+:      :+:    :+:   */
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

static void	destroy_hittable(void *hittable)
{
	((t_hittable *)hittable)->destroy((t_hittable *)hittable);
}

static void	destroy_material(void *material)
{
	((t_material *)material)->destroy((t_material *)material);
}

static void	destroy_texture(void *texture)
{
	((t_texture *)texture)->destroy((t_texture *)texture);
}

void	scene_destroy(t_scene *scene)
{
	if (scene->res.primitives)
		ptrarr_destroy(scene->res.primitives, destroy_hittable);
	if (scene->res.materials)
		ptrarr_destroy(scene->res.materials, destroy_material);
	if (scene->res.textures)
		ptrarr_destroy(scene->res.textures, destroy_texture);
	if (scene->world)
		scene->world->destroy(scene->world);
	if (scene->objects)
		scene->objects->destroy(scene->objects);
	free(scene);
}
