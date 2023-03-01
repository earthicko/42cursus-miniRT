#include <stdlib.h>
#include "libft.h"
#include "geometry.h"
#include "material.h"
#include "hittable_internal.h"

t_hittable	*hittable_xy_rectangle_create(t_point center,
											t_len_rect len,
											double k,
											t_material *material)
{
	t_hittable_xy_rectangle	*xy_rect;

	xy_rect = malloc(sizeof(t_hittable_xy_rectangle));
	if (!xy_rect)
		return (NULL);
	ft_memset(xy_rect, 0, sizeof(t_hittable_xy_rectangle));
	xy_rect->hit = hit_xy_rectangle;
	xy_rect->material = material;
	xy_rect->x0 = center.i[X] - len.i[WIDTH] / 2;
	xy_rect->x1 = center.i[X] + len.i[WIDTH] / 2;
	xy_rect->y0 = center.i[Y] - len.i[HEIGHT] / 2;
	xy_rect->y1 = center.i[Y] + len.i[HEIGHT] / 2;
	xy_rect->k = k;
	return ((t_hittable *)xy_rect);
}

t_hittable	*hittable_yz_rectangle_create(t_point center,
											t_len_rect len,
											double k,
											t_material *material)
{
	t_hittable_yz_rectangle	*yz_rect;

	yz_rect = malloc(sizeof(t_hittable_yz_rectangle));
	if (!yz_rect)
		return (NULL);
	ft_memset(yz_rect, 0, sizeof(t_hittable_yz_rectangle));
	yz_rect->hit = hit_yz_rectangle;
	yz_rect->material = material;
	yz_rect->y0 = center.i[Y] - len.i[WIDTH] / 2;
	yz_rect->y1 = center.i[Y] + len.i[WIDTH] / 2;
	yz_rect->z0 = center.i[Z] - len.i[HEIGHT] / 2;
	yz_rect->z1 = center.i[Z] + len.i[HEIGHT] / 2;
	yz_rect->k = k;
	return ((t_hittable *)yz_rect);
}

t_hittable	*hittable_zx_rectangle_create(t_point center,
											t_len_rect len,
											double k,
											t_material *material)
{
	t_hittable_zx_rectangle	*zx_rect;

	zx_rect = malloc(sizeof(t_hittable_zx_rectangle));
	if (!zx_rect)
		return (NULL);
	ft_memset(zx_rect, 0, sizeof(t_hittable_zx_rectangle));
	zx_rect->hit = hit_zx_rectangle;
	zx_rect->material = material;
	zx_rect->z0 = center.i[Z] - len.i[WIDTH] / 2;
	zx_rect->z1 = center.i[Z] + len.i[WIDTH] / 2;
	zx_rect->x0 = center.i[X] - len.i[HEIGHT] / 2;
	zx_rect->x1 = center.i[X] + len.i[HEIGHT] / 2;
	zx_rect->k = k;
	return ((t_hittable *)zx_rect);
}
