#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "ptrarr.h"
#include "libft.h"
#include "msgdef.h"
#include "texture.h"
#include "xpmwrapper_internal.h"

void	xpmwrapper_destroy(t_xpmwrapper *xpm)
{
	if (xpm->colors)
		free(xpm->colors);
	free(xpm);
}

static void	destroy_pchar(void *pchar)
{
	free((char *)pchar);
}

static t_xpmwrapper	*xpmwrapper_create_empty(t_xpmheader *header)
{
	t_xpmwrapper	*xpm;

	xpm = malloc(sizeof(t_xpmwrapper));
	if (!xpm)
		return (NULL);
	ft_bzero(xpm, sizeof(t_xpmwrapper));
	xpm->colors = malloc(sizeof(t_color) * header->columns * header->rows);
	if (!xpm->colors)
	{
		xpmwrapper_destroy(xpm);
		return (NULL);
	}
	xpm->width = header->columns;
	xpm->height = header->rows;
	xpm->x_range.min = 0;
	xpm->x_range.max = xpm->width - 1;
	xpm->y_range.min = 0;
	xpm->y_range.max = xpm->height - 1;
	return (xpm);
}

static void	xpmwrapper_create_init(const char *filename,
				t_xpmwrapper **xpm, t_ptrarr **lines_buf, t_xpmheader *header)
{
	(*lines_buf) = load_file(filename);
	if (!(*lines_buf))
		return ;
	if (parse_xpm_header(header, (*lines_buf)))
	{
		ptrarr_destroy((*lines_buf), destroy_pchar);
		return ;
	}
	*xpm = xpmwrapper_create_empty(header);
	if (!(*xpm))
	{
		ptrarr_destroy((*lines_buf), destroy_pchar);
		return ;
	}
}

t_xpmwrapper	*xpmwrapper_create(const char *filename, int rotation, int flip)
{
	t_xpmwrapper		*xpm;
	t_ptrarr			*lines;
	static t_xpmheader	header;

	xpmwrapper_create_init(filename, &xpm, &lines, &header);
	if (!xpm)
		return (NULL);
	if (parse_xpm_content(xpm, &header, lines))
	{
		xpmwrapper_destroy(xpm);
		ptrarr_destroy(lines, destroy_pchar);
		return (NULL);
	}
	if (xpmwrapper_transform(xpm, rotation, flip))
		printf("%s: Failed to transform image %s.\n", __func__, filename);
	ptrarr_destroy(lines, destroy_pchar);
	return (xpm);
}
