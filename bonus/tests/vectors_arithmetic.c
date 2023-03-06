#include <stdio.h>
#include "geometry.h"
#include "print.h"

void	vec3_setval(t_vec3 *vec, double a, double b, double c);

void	test_vec3_add_vec3(void)
{
	t_vec3	a;
	t_vec3	b;
	t_vec3	c;

	vec3_setval(&a, 1, 2, 3);
	vec3_setval(&b, 4, 5, 6);
	vec3_add_vec3(&c, &a, &b);
	print_vec3(&a);printf(" + ");print_vec3(&b);printf(" = ");print_vec3(&c);printf("\n");
	print_vec3(&a);
	vec3_add_vec3_inplace(&a, &b);
	printf(" += ");print_vec3(&b);printf(" = ");print_vec3(&a);printf("\n");
}

void	test_vec3_sub_vec3(void)
{
	t_vec3	a;
	t_vec3	b;
	t_vec3	c;

	vec3_setval(&a, 1, 2, 3);
	vec3_setval(&b, 4, 5, 6);
	vec3_sub_vec3(&c, &a, &b);
	print_vec3(&a);printf(" - ");print_vec3(&b);printf(" = ");print_vec3(&c);printf("\n");
	print_vec3(&a);
	vec3_sub_vec3_inplace(&a, &b);
	printf(" -= ");print_vec3(&b);printf(" = ");print_vec3(&a);printf("\n");
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
	print_vec3(&a);printf(" . ");print_vec3(&b);printf(" = %.2f\n", dot);
	vec3_cross_vec3(&c, &a, &b);
	print_vec3(&b);printf(" x ");print_vec3(&b);printf(" = ");print_vec3(&c);printf("\n");
}

void	test_vec3_mult(void)
{
	t_vec3	a;
	t_vec3	b;
	t_vec3	c;

	vec3_setval(&a, 1, 2, 3);
	vec3_setval(&b, 4, 5, 6);
	vec3_mult_num(&c, &a, 2.0);
	print_vec3(&a);printf(" * 2.0 = ");print_vec3(&c);printf("\n");
	print_vec3(&a);
	vec3_mult_num_inplace(&a, 0.5);
	printf(" *= 0.5 = ");print_vec3(&a);printf("\n");
}
