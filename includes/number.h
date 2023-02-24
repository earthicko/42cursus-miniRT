#ifndef NUMBER_H
# define NUMBER_H

# define DOUBLE_E 1e-8

double	rand_double(void);
double	rand_double_range(double min, double max);
int		rand_range(int min, int max);

double	rad_to_deg(double rad);
double	deg_to_rad(double deg);

int		is_near_zero(double num);

#endif
