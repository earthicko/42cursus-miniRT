#include <stdio.h>
#include "hittable.h"
#include "ray.h"
#include "camera.h"
#include "print.h"

void	print_aa_rect(const t_hittable *hittable)
{
	t_hittable_aa_rectangle	*aarect;

	aarect = (t_hittable_aa_rectangle *)hittable;
	printf("aa rect (axis %d, offset %.2f, range %.2f-%.2f, %.2f-%.2f, norm ",
		aarect->axis, aarect->offset,
		aarect->range[0].min, aarect->range[0].max,
		aarect->range[1].min, aarect->range[1].max);
	print_vec3(&aarect->outward_norm);
	printf(")\n");
}

void	print_box(const t_hittable *box)
{
	t_hittable_transform	*tbox;
	t_hittable_aa_box		*aabox;
	int						i;

	tbox = (t_hittable_transform *)box;
	aabox = (t_hittable_aa_box *)tbox->base;
	printf("box object to world: \n");
	print_mtx44(&tbox->o_to_w);
	i = 0;
	while (i < 6)
	{
		print_aa_rect(((t_hittable_list *)aabox->faces)->elements->data[i]);
		printf("\n");
		i++;
	}
}
