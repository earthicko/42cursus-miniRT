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

void	print_cylinder_info(const t_cylinder_info *info)
{
	printf("cylinder (center ");
	print_vec3(&info->center);
	printf(", axis ");
	print_vec3(&info->axis);
	printf(", r %.2f h %.2f", info->radius, info->height);
	printf(")");
}

void	print_bbox(const t_bbox *bbox)
{
	printf("bbox (");
	if (bbox->hit == 0)
	{
		printf("empty");
	}
	else
	{
		print_vec3(&bbox->min);
		printf(" -> ");
		print_vec3(&bbox->max);
	}
	printf(")");
}
