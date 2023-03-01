#include <stddef.h>
#include "parser_internal.h"

t_patternmatcher	unique_patternmatcher_manager(int i)
{
	static const t_patternmatcher	unique_matcher[N_IDENTIFIER_UNIQUE] = {
		is_ambient_lighting,
		is_camera
	};

	if (i < 0 || i >= N_IDENTIFIER_UNIQUE)
		return (NULL);
	return (unique_matcher[i]);
}

t_builder	unique_builder_manager(int i)
{
	static const t_builder			unique_builder[N_IDENTIFIER_UNIQUE] = {
		build_ambient_lighting,
		build_camera
	};

	if (i < 0 || i >= N_IDENTIFIER_UNIQUE)
		return (NULL);
	return (unique_builder[i]);
}

t_patternmatcher	common_patternmatcher_manager(int i)
{
	static const t_patternmatcher	common_matcher[N_IDENTIFIER_COMMON] = {
		is_light,
		is_sphere,
		is_plane,
		is_cylinder,
		is_cone,
		is_texture_solid,
		is_texture_checker,
		is_material_lambertian,
		is_material_metal,
		is_material_dielectric
	};

	if (i < 0 || i >= N_IDENTIFIER_COMMON)
		return (NULL);
	return (common_matcher[i]);
}

t_builder	common_builder_manager(int i)
{
	static const t_builder			common_builder[N_IDENTIFIER_COMMON] = {
		build_light,
		build_sphere,
		build_plane,
		build_cylinder,
		build_cone,
		build_texture_solid,
		build_texture_checker,
		build_material_lambertian,
		build_material_metal,
		build_material_dielectric
	};

	if (i < 0 || i >= N_IDENTIFIER_COMMON)
		return (NULL);
	return (common_builder[i]);
}
