#include <stdio.h>
#include "texture_bonus.h"
#include "print_bonus.h"

void	test_solid(void)
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
}

void	test_checker_loop(t_texture *checker)
{
	t_color	color;
	t_uv	uv;
	t_point	p;
	int		i;

	i = 0;
	while (i < 10)
	{
		vec2_setval(&uv, 0.1 * i, 0.4);
		vec3_setval(&p, 0 * i, 1 * i, 2 * i);
		checker->get_color_at(checker, &color, &uv, &p);
		printf("uv ");
		print_vec2(&uv);
		printf(" output color: ");
		print_vec3(&color);
		printf("\n");
		i++;
	}
}

void	test_checker(void)
{
	t_texture	*colors[2];
	t_color		color;
	t_texture	*checker;

	vec3_setval(&color, 1, 1, 1);
	colors[0] = texture_solid_create(color);
	vec3_setval(&color, 0, 0, 0);
	colors[1] = texture_solid_create(color);
	checker = texture_checker_create(colors[0], colors[1], 10.0);
	test_checker_loop(checker);
}

int	main(void)
{
	test_solid();
	test_checker();
	return (0);
}
