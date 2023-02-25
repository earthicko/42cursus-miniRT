#include "material_internal.h"

void	material_emit(t_material *self,
	t_color *out, const t_hit_record *hitrec)
{
	(void)self;
	(void)hitrec;
	out->i[0] = 0;
	out->i[1] = 0;
	out->i[2] = 0;
}
