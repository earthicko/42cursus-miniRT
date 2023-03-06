#ifndef MLX_INTERFACE_INTERNAL_H
# define MLX_INTERFACE_INTERNAL_H

# include "mlx_interface.h"

enum e_mlxmanmode
{
	MLXMAN_GET = 0,
	MLXMAN_SET
};

void	mlxmanager(int mode, void **buf);

#endif
