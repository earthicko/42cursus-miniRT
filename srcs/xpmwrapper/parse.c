#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "ptrarr.h"
#include "libft.h"
#include "msgdef.h"
#include "texture.h"
#include "xpmwrapper_internal.h"

static t_color	map_color(int rgb[3])
{
	t_color			mappedcolor;
	const t_minmax	in = {0, 255};
	const t_minmax	out = {0, 1};

	mappedcolor.i[0] = map_minmax((double)rgb[0], &in, &out);
	mappedcolor.i[1] = map_minmax((double)rgb[1], &in, &out);
	mappedcolor.i[2] = map_minmax((double)rgb[2], &in, &out);
	return (mappedcolor);
}

int	parse_xpm_info(t_xpmheader *header, const char *secondline)
{
	char	**tokens;
	int		stat;

	tokens = ft_split_by_chars(secondline, " \",");
	if (!tokens)
		return (CODE_ERROR_MALLOC);
	stat = 0;
	stat |= ft_atoi_if_valid(tokens[0], &header->columns);
	stat |= ft_atoi_if_valid(tokens[1], &header->rows);
	stat |= ft_atoi_if_valid(tokens[2], &header->colors);
	stat |= ft_atoi_if_valid(tokens[3], &header->chars_per_pixel);
	ft_free_strarr(tokens);
	if (stat)
		return (CODE_ERROR_DATA);
	return (CODE_OK);
}

int	parse_xpm_colormap(t_xpmheader *header, const char *line)
{
	int	rgb[3];
	int	idx;

	idx = get_color_idx(line + 1, header->chars_per_pixel);
	if (line[header->chars_per_pixel + 4] != '#')
	{
		line = get_x11colorcode(line + header->chars_per_pixel + 4);
		if (!line)
			return (CODE_ERROR_DATA);
		rgb[0] = hex_to_int(line + 1);
		rgb[1] = hex_to_int(line + 1);
		rgb[2] = hex_to_int(line + 1);
	}
	else
	{
		rgb[0] = hex_to_int(line + header->chars_per_pixel + 5);
		rgb[1] = hex_to_int(line + header->chars_per_pixel + 7);
		rgb[2] = hex_to_int(line + header->chars_per_pixel + 9);
	}
	header->map[idx] = map_color(rgb);
	return (CODE_OK);
}

int	parse_xpm_header(t_xpmheader *header, t_ptrarr *lines)
{
	int		i;

	if (lines->len < 2)
		return (CODE_ERROR_DATA);
	if (((char *)(lines->data[0]))[ft_strlen((char *)(lines->data[0])) - 1]
		!= '{')
		return (CODE_ERROR_DATA);
	if (parse_xpm_info(header, lines->data[1]))
		return (CODE_ERROR_DATA);
	i = 2;
	while (i < 2 + header->colors)
	{
		if (parse_xpm_colormap(header, lines->data[i]))
			return (CODE_ERROR_DATA);
		i++;
	}
	return (CODE_OK);
}

int	parse_xpm_content(t_xpmwrapper *xpm, t_xpmheader *header, t_ptrarr *lines)
{
	int			idx;
	int			x;
	int			y;
	const char	*cursor;

	y = 0;
	while (y < header->rows)
	{
		cursor = lines->data[2 + header->colors + y];
		if (ft_strlen(cursor)
			< (size_t)(2 + header->columns * header->chars_per_pixel))
			return (CODE_ERROR_DATA);
		cursor += 1;
		x = 0;
		while (x < header->columns)
		{
			idx = get_color_idx(cursor, header->chars_per_pixel);
			xpm->colors[xpm->width * (xpm->height - y - 1) + x]
				= header->map[idx];
			cursor += header->chars_per_pixel;
			x++;
		}
		y++;
	}
	return (CODE_OK);
}
