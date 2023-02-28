#include <stdlib.h>
#include "texture_internal.h"

void	texture_destroy(t_texture *self)
{
	free(self->name);
	free(self);
}
