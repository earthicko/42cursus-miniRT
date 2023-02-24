#include "material_internal.h"

void	material_emit(t_material *self,
	t_color *out, const t_uv *uv, const t_point *p)
{
	(void)self;
	(void)uv;
	(void)p;
	out->i[0] = 0;
	out->i[1] = 0;
	out->i[2] = 0;
}
