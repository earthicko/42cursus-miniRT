#include "libft.h"
#include "geometry.h"

// TODO: 외적 수정하면서 생긴 부수적인 문제 해결할 것
// A 0.02 255,255,255
// C 40,0.0, 20   -1, 0, 0   120
// l -40.0,50.0,0.0   0.6    10,0,255
// cy 0.0,0.0,0.0     0.0,0.0,1.0  20  20  0,0,255
// 원기둥이 이상하게 보이는듯?

void	vec3_cross_vec3(t_vec3 *out, const t_vec3 *a, const t_vec3 *b)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		out->i[i] = a->i[(i + 1) % 3] * b->i[(i + 2) % 3]
			- a->i[(i + 2) % 3] * b->i[(i + 1) % 3];
		i++;
	}
}
