#ifndef MATERIAL_H
# define MATERIAL_H

# include "geometry.h"
# include "ray.h"
# include "hittable.h"
# include "texture.h"

typedef struct s_hit_record	t_hit_record;
typedef struct s_material	t_material;

typedef struct s_scatter_record
{
	t_color	albedo;
	t_ray	scattered;
}	t_scatter_record;

typedef void				(*t_material_emit)(t_material *self,
	t_color *out, const t_uv *uv, const t_point *p);

typedef t_bool				(*t_material_scatter)(t_material *self,
	t_scatter_record *out, const t_ray *ray_in, const t_hit_record *hit);

typedef struct s_material
{
	t_material_emit		emit;
	t_material_scatter	scatter;
}	t_material;

typedef struct s_material_lambertian
{
	t_material_emit		emit;
	t_material_scatter	scatter;
	t_texture			*albedo;
}	t_material_lambertian;

typedef struct s_material_metal
{
	t_material_emit		emit;
	t_material_scatter	scatter;
	t_texture			*albedo;
	double				fuzz;
}	t_material_metal;

typedef struct s_material_dielectric
{
	t_material_emit		emit;
	t_material_scatter	scatter;
	double				ior;
}	t_material_dielectric;

typedef struct s_material_diffuse_light
{
	t_material_emit		emit;
	t_material_scatter	scatter;
	t_texture			*emitter;
}	t_material_diffuse_light;

t_material	*material_lambertian_create(t_texture *albedo);
t_material	*material_metal_create(t_texture *albedo, double fuzz);
t_material	*material_dielectric_create(double ior);
t_material	*material_diffuse_light_create(t_texture *emitter);

#endif
