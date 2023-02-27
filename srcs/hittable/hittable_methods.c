#include "hittable.h"

t_bool	hittable_has_bbox(t_hittable *self)
{
	if (self->bbox.hit == 0)
		return (FALSE);
	return (TRUE);
}
