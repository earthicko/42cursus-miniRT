#include <stdio.h>
#include "geometry.h"

void	test_vec3_add_vec3(void);
void	test_vec3_sub_vec3(void);
void	test_vec3_dot_cross(void);
void	test_vec3_mult(void);

void	test_vec3_rand(void)
{
	t_vec3	out;

	vec3_rand(&out, -10, 10);
	printf("rand vec (%.2f, %.2f, %.2f)\n", out.i[0], out.i[1], out.i[2]);
	vec3_get_random_in_unit_sphere(&out);
	printf("rand vec in unit sphere (%.2f, %.2f, %.2f)\n",
		out.i[0], out.i[1], out.i[2]);
	vec3_get_random_unit(&out);
	printf("rand vec in unit (%.2f, %.2f, %.2f)\n",
		out.i[0], out.i[1], out.i[2]);
}

void	test_vec3_len(void)
{
	t_vec3	a;
	t_vec3	b;
	t_vec3	c;

	vec3_setval(&a, 1, 2, 3);
	vec3_setval(&b, 4, 5, 6);
	printf("(%.2f, %.2f, %.2f) len = %.2f\n",
		a.i[0], a.i[1], a.i[2], vec3_get_len(&a));
	printf("(%.2f, %.2f, %.2f) len = %.2f\n",
		b.i[0], b.i[1], b.i[2], vec3_get_len(&b));
	printf("(%.2f, %.2f, %.2f) len^2 = %.2f\n",
		a.i[0], a.i[1], a.i[2], vec3_get_len_sq(&a));
	printf("(%.2f, %.2f, %.2f) len^2 = %.2f\n",
		b.i[0], b.i[1], b.i[2], vec3_get_len_sq(&b));
	vec3_get_unit(&c, &a);
	printf("unit of (%.2f, %.2f, %.2f) = (%.2f, %.2f, %.2f)\n",
		a.i[0], a.i[1], a.i[2], c.i[0], c.i[1], c.i[2]);
	vec3_get_unit(&c, &b);
	printf("unit of (%.2f, %.2f, %.2f) = (%.2f, %.2f, %.2f)\n",
		b.i[0], b.i[1], b.i[2], c.i[0], c.i[1], c.i[2]);
}

int	main(void)
{
	test_vec3_add_vec3();
	test_vec3_sub_vec3();
	test_vec3_dot_cross();
	test_vec3_mult();
	test_vec3_rand();
	test_vec3_len();
	return (0);
}
