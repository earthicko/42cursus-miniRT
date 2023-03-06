#ifndef MATERIAL_INTERNAL_H
# define MATERIAL_INTERNAL_H

# include "material.h"

void		material_emit(t_material *self,
				t_color *out, const t_hit_record *hitrec);
void		material_diffuse_light_emit(t_material *self,
				t_color *out, const t_hit_record *hitrec);

t_bool		material_lambertian_scatter(
				t_material *self,
				t_scatter_record *out,
				const t_ray *ray_in,
				const t_hit_record *hit);
t_bool		material_diffuse_light_scatter(
				t_material *self,
				t_scatter_record *out,
				const t_ray *ray_in,
				const t_hit_record *hit);

#endif
