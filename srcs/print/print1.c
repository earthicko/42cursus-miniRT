#include <stdio.h>
#include "hittable.h"
#include "ray.h"
#include "camera.h"
#include "print.h"

void	print_hit_record(const t_hit_record *rec)
{
	printf("hit record p");
	print_vec3(&rec->p);
	printf(" normal ");
	print_vec3(&rec->normal);
	printf(" %.2f ", rec->t);
	printf(" is front: %d", rec->is_front);
}

void	print_scatter_record(const t_scatter_record *rec)
{
	printf("scatter record color ");
	print_vec3(&rec->albedo);
	printf(" ray ");
	print_ray(&rec->scattered);
}
