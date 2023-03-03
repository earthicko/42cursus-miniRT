#include <stddef.h>
#include "parser_internal.h"

char	*tokenname_manager(int i)
{
	static const char	*names[N_IDENTIFIER] = {
		IDENTIFIER_SETTING_DISPLAY,
		IDENTIFIER_SETTING_CAMERA,
		IDENTIFIER_SETTING_RENDERER,
		IDENTIFIER_AMBIENTLIGHTING,
		IDENTIFIER_CAMERA,
		IDENTIFIER_LIGHT,
		IDENTIFIER_SPHERE,
		IDENTIFIER_PLANE,
		IDENTIFIER_CYLINDER,
		IDENTIFIER_CONE,
		IDENTIFIER_BOX,
		IDENTIFIER_TEXTURE_SOLID,
		IDENTIFIER_TEXTURE_CHECKER,
		IDENTIFIER_TEXTURE_IMAGE,
		IDENTIFIER_MATERIAL_LAMBERTIAN,
		IDENTIFIER_MATERIAL_METAL,
		IDENTIFIER_MATERIAL_DIELECTRIC
	};

	if (i < 0 || i >= N_IDENTIFIER)
		return (NULL);
	return ((char *)names[i]);
}

t_wordtester	wordtester_manager(int i)
{
	static const t_wordtester	testers[4] = {
		is_identifier,
		is_number,
		is_comma,
		is_word
	};

	if (i < 0 || i >= N_TOKENTYPE)
		return (NULL);
	return (testers[i]);
}
