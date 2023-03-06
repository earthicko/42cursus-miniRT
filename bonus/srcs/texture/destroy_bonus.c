#include <stdlib.h>
#include "texture_bonus.h"

void	texture_destroy(t_texture *self)
{
	free(self->name);
	free(self);
}
