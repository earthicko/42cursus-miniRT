#include <stddef.h>
#include <stdio.h>
#include "libft.h"
#include "msgdef.h"
#include "scene.h"

t_texture	*scene_search_texture(t_scene *scene, const char *name)
{
	int			i;
	t_texture	*cursor;

	i = 0;
	while (i < scene->res.textures->len)
	{
		cursor = ptrarr_get(scene->res.textures, i);
		if (is_samestr(cursor->name, (char *)name))
			return (cursor);
		i++;
	}
	printf("%s: texture %s not found.\n", EXEC_NAME, name);
	return (NULL);
}
