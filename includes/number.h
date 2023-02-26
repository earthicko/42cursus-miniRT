#ifndef NUMBER_H
# define NUMBER_H

# define DOUBLE_E	1e-8
# define DOUBLE_INF	999999999

typedef struct s_minmax
{
	double	min;
	double	max;
}	t_minmax;

double	rand_double(void);
double	rand_double_range(double min, double max);
int		rand_range(int min, int max);

double	rad_to_deg(double rad);
double	deg_to_rad(double deg);

int		is_near_zero(double num);
double	map_minmax(double x, const t_minmax *in, const t_minmax *out);
int		clamp_int(int x, int min, int max);

#endif
