#ifndef MATERIAL_H
# define MATERIAL_H

# include "geometry.h"
# include "ray.h"
# include "hit_record_dummy.h"
# include "texture.h"

typedef struct s_scatter_record
{
	t_color	albedo;
	t_ray	scattered;
}	t_scatter_record;

typedef struct s_material
{
	void	(*emit)(
			t_material *, t_color *, t_uv, t_point *);
	t_bool	((*scatter)(
			t_material *, t_scatter_record *, t_ray *, t_hit_record *));
}	t_material;

typedef struct s_material_lambertian
{
	void		(*emit)(
			t_material *, t_color *, t_uv, t_point *);
	t_bool		((*scatter)(
			t_material *, t_scatter_record *, t_ray *, t_hit_record *));
	t_texture	*albedo;
}	t_material_lambertian;

typedef struct s_material_metal
{
	void		(*emit)(
			t_material *, t_color *, t_uv, t_point *);
	t_bool		((*scatter)(
			t_material *, t_scatter_record *, t_ray *, t_hit_record *));
	t_texture	*albedo;
	double		fuzz;
}	t_material_metal;

typedef struct s_material_dielectric
{
	void		(*emit)(
			t_material *, t_color *, t_uv, t_point *);
	t_bool		((*scatter)(
			t_material *, t_scatter_record *, t_ray *, t_hit_record *));
	double		ior;
}	t_material_dielectric;

typedef struct s_material_diffuse_light
{
	void		(*emit)(
			t_material *, t_color *, t_uv, t_point *);
	t_bool		((*scatter)(
			t_material *, t_scatter_record *, t_ray *, t_hit_record *));
	t_texture	*emitter;
}	t_material_diffuse_light;

t_material	*material_lambertian_create(t_texture *albedo);
t_material	*material_metal_create(t_texture *albedo, double fuzz);
t_material	*material_dielectric_create(double ior);
t_material	*material_diffuse_light_create(t_texture *emitter);

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
