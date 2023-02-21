#include <stdio.h>
#include "texture.h"
#include "print.h"

int	main(void)
{
	t_texture	*texture_solid;
	t_color		color;
	t_color		color_out;
	t_uv		uv;

	vec3_setval(&color, 0.8, 0.5, 0);
	vec2_setval(&uv, 0.2, 0.3);
	texture_solid = texture_solid_create(color);
	texture_solid->get_color_at(texture_solid, &color_out, &uv, NULL);
	printf("output color: ");
	print_vec3(&color_out);
	printf("\n");
	return (0);
}
