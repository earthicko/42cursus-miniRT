#include "mlx_interface.h"
#include "renderer.h"

int	mlx_key_interface(int k, void *param)
{
	t_renderer	*renderer;

	renderer = param;
	(void)renderer;
	if (k == KEYCODE_ESC)
		exit_program(param);
	return (0);
}
