#include "material.h"

void	material_emit(t_material *self, t_color *out, t_uv uv, t_point *p)
{
	(void)self;
	(void)uv;
	(void)p;
	out->i[0] = 0;
	out->i[1] = 0;
	out->i[2] = 0;
}
