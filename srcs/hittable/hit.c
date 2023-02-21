#include <math.h>
#include "libft_def.h"
#include "geometry.h"
#include "hittable.h"
#include "objects.h"

#define A 0
#define B 1
#define C 2

// TODO: 이차방정식 판별식, 근 구하는 함수 따로 utils로 빼기
t_bool	hit_sphere(t_hittable *hittable, t_ray *r, t_pair t, t_hit_record *rec)
{
	t_sphere	*this;
	t_vec3		oc;
	double		coef[3];		
	double		dscrm;			
	double		root;

	this = (t_sphere *)hittable;
	vec3_sub_vec3(&oc, &r->orig, &this->center);
	coef[A] = vec3_dot_vec3(&r->dir, &r->dir);
	coef[B] = 2 * vec3_dot_vec3(&oc, &r->dir);
	coef[C] = vec3_dot_vec3(&oc, &oc) - pow(this->radius, 2);
	dscrm = pow(coef[B] / 2, 2) - coef[A] * coef[C];
	if (dscrm < 0)
		return (FALSE);
	root = (-coef[B] / 2 - sqrt(dscrm)) / coef[A];
	if (root < t.min || root > t.max)
	{
		root = (-coef[B] / 2 + sqrt(dscrm)) / coef[A];
		if (root < t.min || root > t.max)
			return (FALSE);
	}
	rec->t = root;
	rec->p = r->at(rec->t);
	// TODO: 법선벡터랑 광선방향으로 구 내부인지 외부인지 판별하는 함수
}