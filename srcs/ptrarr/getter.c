#include "ptrarr.h"

void	*ptrarr_get(const t_ptrarr *arr, int i)
{
	while (i < 0)
		i += arr->len;
	return ((void *)arr->data[i % arr->len]);
}

void	*ptrarr_getfirst(const t_ptrarr *arr)
{
	return (ptrarr_get(arr, 0));
}

void	*ptrarr_getlast(const t_ptrarr *arr)
{
	return (ptrarr_get(arr, arr->len - 1));
}
