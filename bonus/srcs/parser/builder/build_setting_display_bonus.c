#include <stdio.h>
#include "libft.h"
#include "msgdef_bonus.h"
#include "ptrarr_bonus.h"
#include "builder_internal_bonus.h"

/*
		display  <width> <height> <multiplier>
		0        1       2        3
	∗ identifier: display
	∗ width of the display
	∗ height of the display
	∗ pixel multiplier
*/
t_bool	is_setting_display(const t_ptrarr *tokens)
{
	static const int	patternlen = 4;
	static const int	pattern[4] = {
		TOKENTYPE_IDENTIFIER,
		TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER,
	};

	if (is_in_pattern(IDENTIFIER_SETTING_DISPLAY, pattern, patternlen, tokens))
		return (TRUE);
	return (FALSE);
}

static int	checkrange_display(int w, int h, int m)
{
	if (w < 1)
	{
		printf("%s: display width "MSG_OUTOFRANGE"\n", EXEC_NAME,
			(double)w, 1.0, DOUBLE_INF);
		return (CODE_ERROR_DATA);
	}
	if (h < 1)
	{
		printf("%s: display height "MSG_OUTOFRANGE"\n", EXEC_NAME,
			(double)h, 1.0, DOUBLE_INF);
		return (CODE_ERROR_DATA);
	}
	if (m < 1)
	{
		printf("%s: display multiplier "MSG_OUTOFRANGE"\n", EXEC_NAME,
			(double)m, 1.0, DOUBLE_INF);
		return (CODE_ERROR_DATA);
	}
	return (CODE_OK);
}

int	build_setting_display(const t_ptrarr *tokens, t_scene *scene)
{
	int	width;
	int	height;
	int	multiplier;

	(void)scene;
	width = ft_atoi(tokens->data[1]);
	height = ft_atoi(tokens->data[2]);
	multiplier = ft_atoi(tokens->data[3]);
	if (checkrange_display(width, height, multiplier))
		return (CODE_ERROR_DATA);
	settingman_display_size(SETTINGMAN_SET, &width, &height, &multiplier);
	printf("%s: display resolution %d * %d (%dx)\n", __func__,
		width, height, multiplier);
	return (CODE_OK);
}
