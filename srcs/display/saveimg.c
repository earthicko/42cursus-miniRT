#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "display_internal.h"
#include "msgdef.h"
#include "settingman.h"

static void	display_save_bmp_init(const t_display *disp,
								t_uchar *fileheader, t_uchar *infoheader)
{
	int			filesize;

	filesize = (BMP_NBYTE_FILEHEADER + BMP_NBYTE_INFOHEADER)
		+ 3 * disp->w_real * disp->h_real;
	ft_bzero(fileheader, sizeof(t_uchar) * BMP_NBYTE_FILEHEADER);
	ft_bzero(infoheader, sizeof(t_uchar) * BMP_NBYTE_INFOHEADER);
	fileheader[0] = 'B';
	fileheader[1] = 'M';
	fileheader[2] = (t_uchar)(filesize);
	fileheader[3] = (t_uchar)(filesize >> 8);
	fileheader[4] = (t_uchar)(filesize >> 16);
	fileheader[5] = (t_uchar)(filesize >> 24);
	fileheader[10] = 54;
	infoheader[0] = 40;
	infoheader[4] = (t_uchar)(disp->w_real);
	infoheader[5] = (t_uchar)(disp->w_real >> 8);
	infoheader[6] = (t_uchar)(disp->w_real >> 16);
	infoheader[7] = (t_uchar)(disp->w_real >> 24);
	infoheader[8] = (t_uchar)(disp->h_real);
	infoheader[9] = (t_uchar)(disp->h_real >> 8);
	infoheader[10] = (t_uchar)(disp->h_real >> 16);
	infoheader[11] = (t_uchar)(disp->h_real >> 24);
	infoheader[12] = 1;
	infoheader[14] = 24;
}

static void	display_save_bmp_write(const t_display *disp, const int fd)
{
	static const t_uchar	bmppad[3];
	int						x;
	int						y;
	char					*cursor;

	y = disp->h_real - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < disp->w_real)
		{
			cursor = (char *)(&disp->image[y * disp->w + x]);
			write(fd, cursor, 3);
			x++;
		}
		write(fd, bmppad, (4 - ((disp->w_real * 3) % 4)) % 4);
		y--;
	}
}

int	display_save_bmp(const t_display *disp, const char *path)
{
	int		fd;
	t_uchar	fileheader[BMP_NBYTE_FILEHEADER];
	t_uchar	infoheader[BMP_NBYTE_INFOHEADER];

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(EXEC_NAME);
		return (CODE_ERROR_IO);
	}
	display_save_bmp_init(disp, fileheader, infoheader);
	write(fd, fileheader, sizeof(fileheader));
	write(fd, infoheader, sizeof(infoheader));
	display_save_bmp_write(disp, fd);
	close(fd);
	printf("Image saved to %s\n", path);
	return (CODE_OK);
}
