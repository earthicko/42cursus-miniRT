#include "number.h"

int	is_near_zero(double num)
{
	return (-DOUBLE_E < num && num < DOUBLE_E);
}
