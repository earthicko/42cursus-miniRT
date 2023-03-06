#include <stdlib.h>
#include "hittable_bonus.h"

t_bool	hittable_has_bbox(t_hittable *self)
{
	if (self->bbox.hit == 0)
		return (FALSE);
	return (TRUE);
}

void	hittable_destroy(t_hittable *self)
{
	free(self);
}
