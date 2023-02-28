#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "number.h"
#include "print.h"
#include "builder_internal.h"

/*
		sp 0.0,0.0,20.6 12.6 10,0,255
	∗ identifier: sp
	∗ x,y,z coordinates of the sphere center: 0.0,0.0,20.6
	∗ the sphere diameter: 12.6
	∗ R,G,B colors in range [0-255]: 10, 0, 255
*/
t_bool	is_sphere(const t_ptrarr *tokens)
{
	static const int	patternlen = 12;
	static const int	pattern[12] = {
		TOKENTYPE_IDENTIFIER,
		TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA,
		TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA,
		TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA,
		TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA,
		TOKENTYPE_NUMBER
	};

	if (is_in_pattern(IDENTIFIER_SPHERE, pattern, patternlen, tokens))
		return (TRUE);
	return (FALSE);
}

// TODO: remove casting to hittable* after return types get sorted out
static int	add_sphere(t_scene *scene, t_point cen, double d, t_material *m)
{
	t_hittable	*sphere;

	sphere = (t_hittable *)hittable_sphere_create(cen, d / 2, m);
	if (!sphere)
		return (CODE_ERROR_MALLOC);
	if (ptrarr_append(scene->res.primitives, sphere))
	{
		free(sphere);
		return (CODE_ERROR_MALLOC);
	}
	if (hittable_list_append(scene->world, sphere)
		|| hittable_list_append(scene->objects, sphere))
		return (CODE_ERROR_MALLOC);
	return (CODE_OK);
}

int	build_sphere(const t_ptrarr *tokens, t_scene *scene)
{
	t_point		cen;
	double		d;
	t_color		color;

	build_vector(&cen, &tokens->data[1]);
	d = ft_atof(tokens->data[6]);
	build_vector(&color, &tokens->data[7]);
	if (is_invalid_length(d / 2) || is_invalid_color(&color))
		return (CODE_ERROR_DATA);
	map_color(&color);
	if (add_texture_solid(scene, color))
		return (CODE_ERROR_MALLOC);
	if (add_material_lambertian(scene, ptrarr_getlast(scene->res.textures)))
		return (CODE_ERROR_MALLOC);
	if (add_sphere(scene, cen, d, ptrarr_getlast(scene->res.materials)))
		return (CODE_ERROR_MALLOC);
	printf("%s: sphere (center ", __func__);
	print_vec3(&cen);
	printf(", radius %.2f, color ", d / 2);
	print_vec3(&color);
	printf(")\n");
	return (CODE_OK);
}
