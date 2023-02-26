#include <stdlib.h>
#include <stdio.h>
#include "print.h"
#include "parser_entities_internal.h"

/*
		pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
	∗ identifier: pl
	∗ x,y,z coordinates of a point in the plane: 0.0,0.0,-10.0
	∗ 3d normalized normal vector.
		In range [-1,1] for each x,y,z axis: 0.0,1.0,0.0
	∗ R,G,B colors in range [0-255]: 0,0,225
*/
t_bool	is_plane(const t_ptrarr *tokens)
{
	static const int	patternlen = 16;
	static const int	pattern[16] = {
		TOKENTYPE_IDENTIFIER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER
	};

	if (is_in_pattern(IDENTIFIER_PLANE, pattern, patternlen, tokens))
		return (TRUE);
	return (FALSE);
}

// TODO: remove casting to hittable* after return types get sorted out
static int	add_plane(t_scene *scene, t_point p, t_vec3 norm, t_material *m)
{
	t_hittable		*plane;
	t_hittable_list	*world;

	plane = (t_hittable *)hittable_plane_create(p, norm, m);
	if (!plane)
		return (CODE_ERROR_MALLOC);
	if (ptrarr_append(scene->res.primitives, plane))
	{
		free(plane);
		return (CODE_ERROR_MALLOC);
	}
	world = (t_hittable_list *)scene->world;
	if (ptrarr_append(world->elements, plane))
		return (CODE_ERROR_MALLOC);
	return (CODE_OK);
}

int	build_plane(const t_ptrarr *tokens, t_scene *scene)
{
	t_point	p;
	t_vec3	norm;
	t_color	color;

	parse_vector(&p, &tokens->data[1]);
	parse_vector(&norm, &tokens->data[6]);
	parse_vector(&color, &tokens->data[11]);
	if (is_invalid_normalized_vec3(&norm), is_invalid_color(&color))
		return (CODE_ERROR_DATA);
	map_color(&color);
	if (add_texture_solid(scene, color))
		return (CODE_ERROR_MALLOC);
	if (add_material_lambertian(scene, ptrarr_getlast(scene->res.textures)))
		return (CODE_ERROR_MALLOC);
	if (add_plane(scene, p, norm, ptrarr_getlast(scene->res.materials)))
		return (CODE_ERROR_MALLOC);
	printf("%s: plane (point ", __func__);
	print_vec3(&p);
	printf(", normal ");
	print_vec3(&norm);
	printf(", color ");
	print_vec3(&color);
	printf(")\n");
	return (CODE_OK);
}
