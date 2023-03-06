#include "mlx_interface_internal_bonus.h"

void	mlxmanager(int mode, void **buf)
{
	static void	*mlx;

	if (mode == MLXMAN_GET)
	{
		if (buf)
			*buf = mlx;
	}
	else
	{
		if (buf)
			mlx = *buf;
	}
}

void	*mlx_interface_get_mlx_ptr(void)
{
	void	*mlx;

	mlxmanager(MLXMAN_GET, &mlx);
	return (mlx);
}
