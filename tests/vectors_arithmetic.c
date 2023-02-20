#include <stdio.h>
#include "geometry.h"

void	vec3_setval(t_vec3 *vec, double a, double b, double c);

void	test_vec3_add_vec3(void)
{
	t_vec3	a;
	t_vec3	b;
	t_vec3	c;

	vec3_setval(&a, 1, 2, 3);
	vec3_setval(&b, 4, 5, 6);
	vec3_add_vec3(&c, &a, &b);
	printf("a + b = (%.2f, %.2f, %.2f)\n", c.i[0], c.i[1], c.i[2]);
	vec3_add_vec3_inplace(&a, &b);
	printf("a += b = (%.2f, %.2f, %.2f)\n", a.i[0], a.i[1], a.i[2]);
}

void	test_vec3_sub_vec3(void)
{
	t_vec3	a;
	t_vec3	b;
	t_vec3	c;

	vec3_setval(&a, 1, 2, 3);
	vec3_setval(&b, 4, 5, 6);
	vec3_sub_vec3(&c, &a, &b);
	printf("a + b = (%.2f, %.2f, %.2f)\n", c.i[0], c.i[1], c.i[2]);
	vec3_sub_vec3_inplace(&a, &b);
	printf("a += b = (%.2f, %.2f, %.2f)\n", a.i[0], a.i[1], a.i[2]);
}

void	test_vec3_dot_cross(void)
{
	t_vec3	a;
	t_vec3	b;
	t_vec3	c;
	double	dot;

	vec3_setval(&a, 1, 2, 3);
	vec3_setval(&b, 4, 5, 6);
	dot = vec3_dot_vec3(&a, &b);
	printf("a . b = %.2f\n", dot);
	vec3_cross_vec3(&c, &a, &b);
	printf("a x b = (%.2f, %.2f, %.2f)\n", c.i[0], c.i[1], c.i[2]);
}

void	test_vec3_mult(void)
{
	t_vec3	a;
	t_vec3	b;
	t_vec3	c;

	vec3_setval(&a, 1, 2, 3);
	vec3_setval(&b, 4, 5, 6);
	vec3_mult_num(&c, &a, 2.0);
	printf("a * 2 = (%.2f, %.2f, %.2f)\n", c.i[0], c.i[1], c.i[2]);
	vec3_mult_num_inplace(&a, 0.5);
	printf("a *= 0.5 = (%.2f, %.2f, %.2f)\n", a.i[0], a.i[1], a.i[2]);
}
