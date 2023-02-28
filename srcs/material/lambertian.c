#include <stdlib.h>
#include "libft.h"
#include "geometry.h"
#include "material_internal.h"

t_material	*material_lambertian_create(t_texture *albedo)
{
	t_material_lambertian	*out;

	out = malloc(sizeof(t_material_lambertian));
	if (!out)
		return (NULL);
	out->emit = material_emit;
	out->scatter = material_lambertian_scatter;
	out->albedo = albedo;
	return ((t_material *)out);
}

t_bool	material_lambertian_scatter(
				t_material *self,
				t_scatter_record *out,
				const t_ray *ray_in,
				const t_hit_record *hit)
{
	t_vec3					random_unit;
	t_vec3					scatter_dir;
	t_material_lambertian	*this;

	(void)ray_in;
	this = (t_material_lambertian *)self;
	vec3_get_random_unit(&random_unit);
	vec3_add_vec3(&scatter_dir, &(hit->normal), &random_unit);
	out->scattered.orig = hit->p;
	if (vec3_is_near_zero(&scatter_dir))
		out->scattered.dir = hit->normal;
	else
		out->scattered.dir = scatter_dir;
	this->albedo->get_color_at(this->albedo, &(out->albedo), hit);
	return (TRUE);
}
