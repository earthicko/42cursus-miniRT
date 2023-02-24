#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "hittable_internal.h"
#include "material.h"
#include "geometry.h"

// TODO: radius 0, 혹은 거의 0인 경우에 대한 예외처리, 파싱단에서 처리하는게 나을듯
// TODO: 필요시 uv 좌표 계산식 추가, the next weekend
// TODO: 직선의 방향벡터가 정규화(길이 1로 설정)되지 않았을 때도 성립하는지 체크

// TODO: outward_norm 길이 1로 정규화를 해주긴 했는데 왜 해야되지? 일단 해두긴 함
t_bool	hit_sphere(t_hittable *hittable, \
					t_ray *ray, \
					t_minmax t, \
					t_hit_record *rec)
{
	t_hittable_sphere	*this;
	t_vec3				oc;
	t_vec3				outward_norm;
	double				coef[3];
	double				root;

	this = (t_hittable_sphere *)hittable;
	vec3_sub_vec3(&oc, &ray->orig, &this->center);
	coef[A] = vec3_dot_vec3(&ray->dir, &ray->dir);
	coef[B] = 2 * vec3_dot_vec3(&oc, &ray->dir);
	coef[C] = vec3_dot_vec3(&oc, &oc) - pow(this->radius, 2);
	if (solve_quadratic_equation(t, coef, &root) == FALSE)
		return (FALSE);
	rec->t = root;
	ray_at(&rec->p, ray, rec->t);
	vec3_sub_vec3(&outward_norm, &rec->p, &this->center);
	vec3_mult_num_inplace(&outward_norm, 1 / this->radius);
	hit_record_set_normal_and_face(rec, ray, &outward_norm);
	rec->material = this->material;
	return (TRUE);
}

t_hittable_sphere	*sphere_create(
								t_point center,
								double radius,
								t_material *material)
{
	t_hittable_sphere	*sphere;

	sphere = malloc(sizeof(t_hittable_sphere));
	if (!sphere)
		return (NULL);
	ft_memset(sphere, 0, sizeof(sphere));
	sphere->center = center;
	sphere->radius = radius;
	sphere->material = material;
	sphere->hit = hit_sphere;
	return (sphere);
}	
