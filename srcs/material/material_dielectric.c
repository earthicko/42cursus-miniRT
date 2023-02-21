#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "geometry.h"
#include "number.h"
#include "material_internal.h"

t_material	*material_dielectric_create(double ior)
{
	t_material_dielectric	*out;

	out = malloc(sizeof(t_material_dielectric));
	if (!out)
		return (NULL);
	out->emit = material_emit;
	out->scatter = material_dielectric_scatter;
	out->ior = ior;
	return ((t_material *)out);
}

void	material_dielectric_scatter_set_sincostheta(
		t_vec3 *unitdir, t_hit_record *hit, double *costheta, double *sintheta)
{
	t_vec3	unitdir_inv;

	vec3_mult_num(&unitdir_inv, unitdir, -1);
	*costheta = fmin(vec3_dot_vec3(&unitdir_inv, &hit->normal), 1.0);
	*sintheta = sqrt(1.0 - *costheta * *costheta);
}

double	material_dialectric_get_reflectance(
		double costheta, double refract_ratio)
{
	double	r0_sq;
	double	r0;

	r0_sq = (1 - refract_ratio) / (1 + refract_ratio);
	r0 = r0_sq * r0_sq;
	return (r0 + (1 - r0) * pow((1 - costheta), 5));
}

t_bool	material_dielectric_can_refract(
		double refract_ratio, double sintheta, double costheta)
{
	double	reflectance;

	if (refract_ratio * sintheta > 1.0)
		return (FALSE);
	reflectance = material_dialectric_get_reflectance(costheta, refract_ratio);
	if (reflectance > rand_double())
		return (FALSE);
	return (TRUE);
}

t_bool	material_dielectric_scatter(
				t_material *self,
				t_scatter_record *out,
				t_ray *ray_in,
				t_hit_record *hit)
{
	t_material_dielectric	*this;
	double					refract_ratio;
	t_vec3					unit_dir;
	double					costheta;
	double					sintheta;

	this = (t_material_dielectric *)self;
	vec3_setval(&out->albedo, 1, 1, 1);
	if (hit->is_front)
		refract_ratio = 1.0 / this->ior;
	else
		refract_ratio = this->ior;
	vec3_get_unit(&unit_dir, &ray_in->dir);
	material_dielectric_scatter_set_sincostheta(
		&unit_dir, hit, &costheta, &sintheta);
	if (material_dielectric_can_refract(refract_ratio, sintheta, costheta))
		vec3_refract(&out->scattered.dir,
			&unit_dir, &hit->normal, refract_ratio);
	else
		vec3_reflect(&out->scattered.dir,
			&unit_dir, &hit->normal);
	out->scattered.orig = hit->p;
	return (TRUE);
}
