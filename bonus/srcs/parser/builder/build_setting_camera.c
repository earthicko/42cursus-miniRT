#include <stdio.h>
#include "libft.h"
#include "msgdef.h"
#include "print.h"
#include "ptrarr.h"
#include "builder_internal.h"

/*
		camera  u , v , w    <focallen>
		0       1 2 3 4 5    6
	∗ identifier: camera
	∗ (u, v, w) of upward direction of camera
	∗ focal length of camera
*/
t_bool	is_setting_camera(const t_ptrarr *tokens)
{
	static const int	patternlen = 7;
	static const int	pattern[7] = {
		TOKENTYPE_IDENTIFIER,
		TOKENTYPE_NUMBER, TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA, TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER,
	};

	if (is_in_pattern(IDENTIFIER_SETTING_CAMERA, pattern, patternlen, tokens))
		return (TRUE);
	return (FALSE);
}

int	build_setting_camera(const t_ptrarr *tokens, t_scene *scene)
{
	t_vec3	up_dir;
	double	focallen;

	(void)scene;
	build_vector(&up_dir, tokens->data + 1);
	focallen = ft_atof(tokens->data[6]);
	if (is_invalid_normalized_vec3(&up_dir) || is_invalid_length(focallen))
		return (CODE_ERROR_DATA);
	vec3_unitize(&up_dir);
	settingman_caminfo(SETTINGMAN_SET, &up_dir, &focallen);
	printf("%s: camera upward direction ", __func__);
	print_vec3(&up_dir);
	printf(" focal length %.2f\n", focallen);
	return (CODE_OK);
}
