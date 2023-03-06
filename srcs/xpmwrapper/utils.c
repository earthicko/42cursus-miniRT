#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "ptrarr.h"
#include "libft.h"
#include "msgdef.h"
#include "texture.h"
#include "xpmwrapper_internal.h"

int	hex_to_int(const char *hex)
{
	int	buf;

	buf = 0;
	if ('0' <= hex[0] && hex[0] <= '9')
		buf += hex[0] - '0';
	else
		buf += hex[0] - 'A' + 10;
	buf *= 16;
	if ('0' <= hex[1] && hex[1] <= '9')
		buf += hex[1] - '0';
	else
		buf += hex[1] - 'A' + 10;
	return (buf);
}

int	get_color_idx(const char *iden, int len)
{
	int	idx;
	int	i;

	idx = iden[0];
	i = 1;
	while (i < len)
	{
		idx *= 255;
		idx += iden[i];
		i++;
	}
	return (idx);
}

static char	*get_x11colorcode_by_idx(int idx)
{
	static char	*colorcodes[X11_COLOR_N] = {
		X11_COLORCODE_BLACK, X11_COLORCODE_WHITE, X11_COLORCODE_GRAY,
		X11_COLORCODE_RED, X11_COLORCODE_GREEN, X11_COLORCODE_BLUE,
		X11_COLORCODE_CYAN, X11_COLORCODE_MAGENTA, X11_COLORCODE_YELLOW,
		X11_COLORCODE_ORANGE, X11_COLORCODE_BROWN,
		X11_COLORCODE_DARKGREEN,
		X11_COLORCODE_DARKBLUE,
		X11_COLORCODE_DARKCYAN,
		X11_COLORCODE_DARKMAGENTA,
		X11_COLORCODE_DARKGRAY,
	};

	if (idx < 0 || idx >= X11_COLOR_N)
		return (NULL);
	return (colorcodes[idx]);
}

char	*get_x11colorcode(const char *colorname)
{
	static char	*colornames[X11_COLOR_N] = {
		X11_COLORNAME_BLACK, X11_COLORNAME_WHITE, X11_COLORNAME_GRAY,
		X11_COLORNAME_RED, X11_COLORNAME_GREEN, X11_COLORNAME_BLUE,
		X11_COLORNAME_CYAN, X11_COLORNAME_MAGENTA, X11_COLORNAME_YELLOW,
		X11_COLORNAME_ORANGE, X11_COLORNAME_BROWN,
		X11_COLORNAME_DARKGREEN,
		X11_COLORNAME_DARKBLUE,
		X11_COLORNAME_DARKCYAN,
		X11_COLORNAME_DARKMAGENTA,
		X11_COLORNAME_DARKGRAY,
	};
	int			i;

	i = 0;
	while (i < X11_COLOR_N)
	{
		if (ft_strncmp(colorname, colornames[i], ft_strlen(colornames[i])) == 0)
			return (get_x11colorcode_by_idx(i));
		i++;
	}
	return (NULL);
}
