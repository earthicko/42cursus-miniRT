#include <stdio.h>
#include <time.h>
#include "libft.h"
#include "material.h"
#include "print.h"

void	test_emit(t_material *material)
{
	t_uv		uv;
	t_point		point;
	t_color		color;

	vec2_setval(&uv, 0.34, 0.21);
	vec3_setval(&point, 12, 34, 56);
	material->emit(material, &color, &uv, &point);
	printf("	emit: ");
	print_vec3(&color);
	printf("\n");
}

void	test_scatter(t_material *material)
{
	t_ray				ray;
	t_hit_record		hit;
	t_scatter_record	scattered;

	vec3_setval(&ray.dir, 1, 0, 0);
	vec3_setval(&ray.orig, 0, 0, 0);
	printf("	scatter: input ");
	print_ray(&ray);
	vec3_setval(&hit.p, 10, 0, 0);
	vec3_setval(&hit.normal, -0.70710678118, 0.70710678118, 0);
	hit.material = material;
	hit.t = 10.0;
	vec2_setval(&hit.uv, 5, 10);
	hit.is_front = TRUE;
	if (material->scatter(material, &scattered, &ray, &hit))
	{
		printf("\n	scatter: albedo ");
		print_vec3(&scattered.albedo);
		printf(", ");
		print_ray(&scattered.scattered);
		printf(" vec len %.5f", vec3_get_len(&scattered.scattered.dir));
		printf("\n");
	}
	else
		printf("\n	scatter: false\n");
}

void	test_material(t_material *material)
{
	test_emit(material);
	test_scatter(material);
}

int	main(void)
{
	t_texture	*solid;
	t_material	*materials[4];
	t_color		color;

	ft_srand(time(NULL));
	vec3_setval(&color, 0.2, 0.3, 0.4);
	solid = texture_solid_create(color);
	materials[0] = material_lambertian_create(solid);
	materials[1] = material_metal_create(solid, 0.0);
	materials[2] = material_dielectric_create(1.55);
	materials[3] = material_diffuse_light_create(solid);
	printf("Lambertian:\n");
	test_material(materials[0]);
	printf("Metal:\n");
	test_material(materials[1]);
	printf("Dielectric:\n");
	test_material(materials[2]);
	printf("Diffuse:\n");
	test_material(materials[3]);
	return (0);
}
