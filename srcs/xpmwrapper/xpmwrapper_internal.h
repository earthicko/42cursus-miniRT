#ifndef XPMWRAPPER_INTERNAL_H
# define XPMWRAPPER_INTERNAL_H

# include "ptrarr.h"
# include "xpmwrapper.h"

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
