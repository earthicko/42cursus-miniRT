#ifndef XPMWRAPPER_INTERNAL_H
# define XPMWRAPPER_INTERNAL_H

# include "ptrarr.h"
# include "xpmwrapper.h"

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

typedef struct s_xpmheader
{
	int		columns;
	int		rows;
	int		colors;
	int		chars_per_pixel;
	t_color	map[XPMWRAPPER_NCOLORS_MAX];
}	t_xpmheader;

t_ptrarr	*load_file(const char *path);

int			hex_to_int(const char *hex);
int			get_color_idx(const char *iden, int len);
char		*get_x11colorcode(const char *colorname);

int			parse_xpm_header(t_xpmheader *header,
				t_ptrarr *lines);
int			parse_xpm_content(t_xpmwrapper *xpm, t_xpmheader *header,
				t_ptrarr *lines);
int			xpmwrapper_transform(t_xpmwrapper *xpmwrapper,
				int rotation, int flip);

#endif
