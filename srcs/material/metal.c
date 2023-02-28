#include <stdlib.h>
#include "libft.h"
#include "geometry.h"
#include "material_internal.h"

t_material	*material_metal_create(t_texture *albedo, double fuzz)
{
	t_material_metal	*out;

	out = malloc(sizeof(t_material_metal));
	if (!out)
		return (NULL);
	out->emit = material_emit;
	out->scatter = material_metal_scatter;
	out->albedo = albedo;
	out->fuzz = fuzz;
	return ((t_material *)out);
}

/*
	reflection = reflection of ray_in by normal
	scattered ray origin = hit point
	scattered ray dir = reflection + fuzz value * random in unit sphere
	if dir is same with normal, scatter success
*/
t_bool	material_metal_scatter(
				t_material *self,
				t_scatter_record *out,
				const t_ray *ray_in,
				const t_hit_record *hit)
{
	t_material_metal	*this;
	t_vec3				in_unit;
	t_vec3				reflection;
	t_vec3				fuzziness;

	this = (t_material_metal *)self;
	vec3_get_unit(&in_unit, &ray_in->dir);
	vec3_reflect(&reflection, &in_unit, &hit->normal);
	out->scattered.orig = hit->p;
	vec3_get_random_in_unit_sphere(&fuzziness);
	vec3_mult_num_inplace(&fuzziness, this->fuzz);
	vec3_add_vec3(&out->scattered.dir, &reflection, &fuzziness);
	if (vec3_dot_vec3(&out->scattered.dir, &hit->normal) > 0)
	{
		this->albedo->get_color_at(this->albedo, &out->albedo, hit);
		return (TRUE);
	}
	return (FALSE);
}
