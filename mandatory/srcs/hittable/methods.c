#include <stdlib.h>
#include "hittable.h"

void	hittable_destroy(t_hittable *self)
{
	free(self);
}
