#ifndef MLX_INTERFACE_INTERNAL_H
# define MLX_INTERFACE_INTERNAL_H

# include "mlx_interface.h"

# define BMP_NBYTE_FILEHEADER	14
# define BMP_NBYTE_INFOHEADER	40

enum e_mlxmanmode
{
	MLXMAN_GET = 0,
	MLXMAN_SET
};

void	mlxmanager(int mode, void **buf);

int		imgwrapper_load(t_imgwrapper *imgwrapper);
int		imgwrapper_transform(t_imgwrapper *imgwrapper);

#endif
