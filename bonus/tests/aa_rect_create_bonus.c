#include <stdlib.h>
#include "hittable_bonus.h"

int	main(void)
{
	t_point		center = {0, 0, 0};
	t_len_rect	len = {10, 10};
	double		k = 5;
	t_hittable	*xy_rect;
	t_hittable	*yz_rect;
	t_hittable	*zx_rect;

	xy_rect = hittable_xy_rectangle_create(center, len, k, 0);
	yz_rect = hittable_yz_rectangle_create(center, len, k, 0);
	zx_rect = hittable_zx_rectangle_create(center, len, k, 0);
	return (0);
}