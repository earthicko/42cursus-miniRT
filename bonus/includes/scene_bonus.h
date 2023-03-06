#ifndef SCENE_BONUS_H
# define SCENE_BONUS_H

# include "ptrarr_bonus.h"
# include "camera_bonus.h"
# include "hittable_bonus.h"

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

t_texture	*scene_search_texture(t_scene *scene, const char *name);
t_material	*scene_search_material(t_scene *scene, const char *name);

#endif
