#ifndef MATERIAL_INTERNAL_H
# define MATERIAL_INTERNAL_H

# include "material.h"

void		material_emit(
				t_material *self, t_color *out, t_uv uv, t_point *p);
void		material_diffuse_light_emit(
				t_material *self, t_color *out, t_uv uv, t_point *p);

t_bool		material_lambertian_scatter(
				t_material *self,
				t_scatter_record *out,
				t_ray *ray_in,
				t_hit_record *hit);
t_bool		material_metal_scatter(
				t_material *self,
				t_scatter_record *out,
				t_ray *ray_in,
				t_hit_record *hit);
t_bool		material_dielectric_scatter(
				t_material *self,
				t_scatter_record *out,
				t_ray *ray_in,
				t_hit_record *hit);
t_bool		material_diffuse_light_scatter(
				t_material *self,
				t_scatter_record *out,
				t_ray *ray_in,
				t_hit_record *hit);

#endif
