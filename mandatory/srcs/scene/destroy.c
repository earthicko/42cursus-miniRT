/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ptrarr.h"
#include "hittable.h"
#include "scene.h"

static void	destroy_hittable(void *hittable)
{
	free(hittable);
}

static void	destroy_material(void *material)
{
	free(material);
}

static void	destroy_texture(void *texture)
{
	free(texture);
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
		hittable_list_destroy(scene->world);
	if (scene->objects)
		hittable_list_destroy(scene->objects);
	free(scene);
}
