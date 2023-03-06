#ifndef NUMBER_H
# define NUMBER_H

# define DOUBLE_E	1e-8
# define DOUBLE_INF	999999999.9

typedef struct s_minmax
{
	double	min;
	double	max;
}	t_minmax;

double	rand_double(void);
double	rand_double_range(double min, double max);
int		rand_range(int min, int max);

int		ft_rand_ts(void);
double	rand_double_ts(void);
double	rand_double_range_ts(double min, double max);
int		rand_range_ts(int min, int max);

double	rad_to_deg(double rad);
double	deg_to_rad(double deg);

int		is_near_zero(double num);
double	map_minmax(double x, const t_minmax *in, const t_minmax *out);
int		clamp_int(int x, int min, int max);
void	swap_double(double *a, double *b);

#endif
