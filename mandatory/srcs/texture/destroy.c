#include <stdlib.h>
#include "texture.h"

void	texture_destroy(t_texture *self)
{
	free(self->name);
	free(self);
}
