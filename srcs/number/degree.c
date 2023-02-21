#include <math.h>

double	rad_to_deg(double rad)
{
	return (rad * (180.0 / M_PI));
}

double	deg_to_rad(double deg)
{
	return (deg / (180.0 / M_PI));
}
