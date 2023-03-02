#include <stdio.h>
#include "libft.h"
#include "msgdef.h"
#include "ptrarr.h"
#include "builder_internal.h"

/*
		renderer  max_depth  n_samples  update_freq_show  update_freq_save
		0         1          2          3                 4
	∗ identifier: renderer
	∗ maximum depth of scattered ray
	∗ number of samples of each pixels
	∗ frequency of viewport update (in sample count)
	∗ frequency of saving image (in sample count)
*/
t_bool	is_setting_renderer(const t_ptrarr *tokens)
{
	static const int	patternlen = 5;
	static const int	pattern[5] = {
		TOKENTYPE_IDENTIFIER,
		TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER,
	};

	if (is_in_pattern(IDENTIFIER_SETTING_RENDERER, pattern, patternlen, tokens))
		return (TRUE);
	return (FALSE);
}

static int	checkrange_renderer(
				int max_depth,
				int n_samples,
				int update_freq_show,
				int update_freq_save)
{
	if (max_depth < 1)
	{
		printf("%s: max_depth "MSG_OUTOFRANGE"\n", EXEC_NAME,
			(double)max_depth, 1.0, DOUBLE_INF);
		return (CODE_ERROR_DATA);
	}
	if (n_samples < 1)
	{
		printf("%s: n_samples "MSG_OUTOFRANGE"\n", EXEC_NAME,
			(double)n_samples, 1.0, DOUBLE_INF);
		return (CODE_ERROR_DATA);
	}
	if (update_freq_show < 1)
	{
		printf("%s: update_freq_show "MSG_OUTOFRANGE"\n", EXEC_NAME,
			(double)update_freq_show, 1.0, DOUBLE_INF);
		return (CODE_ERROR_DATA);
	}
	if (update_freq_save < 1)
	{
		printf("%s: update_freq_save "MSG_OUTOFRANGE"\n", EXEC_NAME,
			(double)update_freq_save, 1.0, DOUBLE_INF);
		return (CODE_ERROR_DATA);
	}
	return (CODE_OK);
}

int	build_setting_renderer(const t_ptrarr *tokens, t_scene *scene)
{
	int	values[4];

	(void)scene;
	values[0] = ft_atoi(tokens->data[1]);
	values[1] = ft_atoi(tokens->data[2]);
	values[2] = ft_atoi(tokens->data[3]);
	values[3] = ft_atoi(tokens->data[4]);
	if (checkrange_renderer(values[0], values[1], values[2], values[3]))
		return (CODE_ERROR_DATA);
	settingman_rendererinfo(SETTINGMAN_SET, values);
	printf("%s: renderer setting ("
		"max depth %d, "
		"%d samples per pixel, "
		"viewport update frequency %d, "
		"image save frequency %d)\n", __func__,
		values[0], values[1], values[2], values[3]);
	return (CODE_OK);
}
