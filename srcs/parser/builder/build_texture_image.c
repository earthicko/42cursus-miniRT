#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "print.h"
#include "builder_internal.h"

static t_bool	match_extension(const char *path, const char *ext)
{
	size_t	start;

	start = ft_strlen(path) - ft_strlen(ext);
	if (ft_strncmp(path + start, ext, ft_strlen(ext) + 1) == 0)
		return (TRUE);
	return (FALSE);
}

/*
		tx_image <name> <file_name.xpm>
		0        1      2
	∗ identifier: tx image
	∗ name: aarbitary given name of the texture
	∗ file path of the texture image
*/
t_bool	is_texture_image(const t_ptrarr *tokens)
{
	static const int	patternlen = 3;
	static const int	pattern[3] = {
		TOKENTYPE_IDENTIFIER,
		TOKENTYPE_WORD,
		TOKENTYPE_WORD,
	};

	if (is_in_pattern(IDENTIFIER_TEXTURE_IMAGE, pattern, patternlen, tokens)
		&& match_extension(tokens->data[2], ".xpm"))
		return (TRUE);
	return (FALSE);
}

static int	add_texture_image(t_scene *scene, const char *name, char *filepath)
{
	t_texture		*image;

	image = texture_image_create(name, filepath);
	if (!image)
		return (CODE_ERROR_MALLOC);
	if (ptrarr_append(scene->res.textures, image))
	{
		texture_destroy(image);
		return (CODE_ERROR_MALLOC);
	}
	return (CODE_OK);
}

int	build_texture_image(const t_ptrarr *tokens, t_scene *scene)
{
	if (add_texture_image(scene, tokens->data[1], (char *)tokens->data[2]))
		return (CODE_ERROR_MALLOC);
	printf("%s: image texture (%s, using file %s)\n", __func__,
		((t_texture *)ptrarr_getlast(scene->res.textures))->name,
		(char *)tokens->data[2]);
	return (CODE_OK);
}
