#ifndef XPMWRAPPER_H
# define XPMWRAPPER_H

# include "geometry.h"
# include "number.h"

# define XPMWRAPPER_CHARSPP_MAX	4
# define XPMWRAPPER_NCOLORS_MAX	16581375
# define X11_COLOR_N				16
# define X11_COLORNAME_BLACK		"black"
# define X11_COLORCODE_BLACK		"#000000"
# define X11_COLORNAME_WHITE		"white"
# define X11_COLORCODE_WHITE		"#FFFFFF"
# define X11_COLORNAME_GRAY			"gray"
# define X11_COLORCODE_GRAY			"#BEBEBE"
# define X11_COLORNAME_RED			"red"
# define X11_COLORCODE_RED			"#FF0000"
# define X11_COLORNAME_GREEN		"green"
# define X11_COLORCODE_GREEN		"#00FF00"
# define X11_COLORNAME_BLUE			"blue"
# define X11_COLORCODE_BLUE			"#0000FF"
# define X11_COLORNAME_CYAN			"cyan"
# define X11_COLORCODE_CYAN			"#00FFFF"
# define X11_COLORNAME_MAGENTA		"magenta"
# define X11_COLORCODE_MAGENTA		"#FF00FF"
# define X11_COLORNAME_YELLOW		"yellow"
# define X11_COLORCODE_YELLOW		"#FFFF00"
# define X11_COLORNAME_ORANGE		"orange"
# define X11_COLORCODE_ORANGE		"#FFA500"
# define X11_COLORNAME_BROWN		"brown"
# define X11_COLORCODE_BROWN		"#A52A2A"
# define X11_COLORNAME_DARKGREEN	"darkgreen"
# define X11_COLORCODE_DARKGREEN	"#006400"
# define X11_COLORNAME_DARKBLUE		"darkblue"
# define X11_COLORCODE_DARKBLUE		"#00008B"
# define X11_COLORNAME_DARKCYAN		"darkcyan"
# define X11_COLORCODE_DARKCYAN		"#008B8B"
# define X11_COLORNAME_DARKMAGENTA	"darkmagenta"
# define X11_COLORCODE_DARKMAGENTA	"#8B008B"
# define X11_COLORNAME_DARKGRAY		"darkgray"
# define X11_COLORCODE_DARKGRAY		"#A9A9A9"

typedef struct s_xpmwrapper
{
	int			width;
	int			height;
	t_minmax	x_range;
	t_minmax	y_range;
	t_color		*colors;
}	t_xpmwrapper;

typedef struct s_xpmheader
{
	int		columns;
	int		rows;
	int		colors;
	int		chars_per_pixel;
	t_color	map[XPMWRAPPER_NCOLORS_MAX];
}	t_xpmheader;

t_xpmwrapper	*xpmwrapper_create(const char *filename,
					int rotation, int flip);
void			xpmwrapper_destroy(t_xpmwrapper *xpm);
void			xpmwrapper_getcolor(t_xpmwrapper *xpm,
					t_color *out, const t_uv *uv);

#endif
