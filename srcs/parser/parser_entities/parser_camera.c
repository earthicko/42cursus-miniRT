#include <stdio.h>
#include "libft.h"
#include "print.h"
#include "../parser_internal.h"

/*
		C -50.0,0,20 0,0,1 70
	∗ identifier: C
	∗ x,y,z coordinates of the view point: -50.0,0,20
	∗ 3d normalized orientation vector.
		In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
	∗ FOV : Horizontal field of view in degrees in range [0,180]: 70
*/
t_bool	is_camera(const t_ptrarr *tokens)
{
	static const int	patternlen = 12;
	static const int	pattern[12] = {
		TOKENTYPE_IDENTIFIER,
		TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA,
		TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA,
		TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA,
		TOKENTYPE_NUMBER,
		TOKENTYPE_COMMA,
		TOKENTYPE_NUMBER,
		TOKENTYPE_NUMBER
	};

	if (is_in_pattern(IDENTIFIER_CAMERA, pattern, patternlen, tokens))
		return (TRUE);
	return (FALSE);
}

static void	camerainfo_init(t_camerainfo *info,
				t_point *viewpoint, t_vec3 *viewdir, double fov)
{
	info->cam_start = *viewpoint;
	vec3_add_vec3(&info->cam_end, viewpoint, viewdir);
	vec3_setval(&info->cam_up, 0, 1, 0);
	info->fov = fov;
	info->focallen = CAM_DEFAULT_FOCALLEN;
	info->pixel_w = CAM_DEFAULT_PIXEL_W;
	info->pixel_h = CAM_DEFAULT_PIXEL_H;
}

int	build_camera(const t_ptrarr *tokens, t_scene *scene)
{
	t_point			viewpoint;
	t_vec3			viewdir;
	double			fov;
	t_camerainfo	info;

	parse_vector(&viewpoint, &tokens->data[1]);
	parse_vector(&viewdir, &tokens->data[6]);
	if (is_invalid_normalized_vec3(&viewdir))
		return (CODE_ERROR_DATA);
	fov = ft_atof(tokens->data[11]);
	if (is_invalid_fov(fov))
		return (CODE_ERROR_DATA);
	camerainfo_init(&info, &viewpoint, &viewdir, fov);
	camera_init(&scene->cam, &info);
	printf("%s: camera viewpoint ", __func__);
	print_vec3(&viewpoint);
	printf(", view direction ");
	print_vec3(&viewdir);
	printf(", fov %.2f\n%s: built ", fov, __func__);
	print_camera(&scene->cam);
	printf("\n");
	return (CODE_OK);
}
