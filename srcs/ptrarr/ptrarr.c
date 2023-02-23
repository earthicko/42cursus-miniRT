#include <stdlib.h>
#include "libft.h"
#include "ptrarr.h"

t_ptrarr	*ptrarr_create(void)
{
	t_ptrarr	*ptrarr;

	ptrarr = malloc(sizeof(t_ptrarr));
	if (!ptrarr)
		return (NULL);
	ptrarr->data = malloc(sizeof(void *) * PTRARR_INITIAL_CAP);
	if (!(ptrarr->data))
	{
		free(ptrarr);
		return (NULL);
	}
	ptrarr->len = 0;
	ptrarr->cap = PTRARR_INITIAL_CAP;
	return (ptrarr);
}

t_ptrarr	*ptrarr_destroy(t_ptrarr *ptrarr, t_bool free_all)
{
	if (free_all)
		ptrarr_free_all_ptr(ptrarr);
	free(ptrarr->data);
	free(ptrarr);
	return (NULL);
}

int	ptrarr_expand(t_ptrarr *ptrarr)
{
	void	**new_data;

	new_data = malloc(sizeof(void *) * ptrarr->cap * 2);
	if (!new_data)
		return (CODE_ERROR_MALLOC);
	ft_memcpy(new_data, ptrarr->data, sizeof(void *) * ptrarr->len);
	free(ptrarr->data);
	ptrarr->data = new_data;
	ptrarr->cap = ptrarr->cap * 2;
	return (CODE_OK);
}

int	ptrarr_append(t_ptrarr *ptrarr, void *data)
{
	if (ptrarr->len == ptrarr->cap)
	{
		if (ptrarr_expand(ptrarr))
			return (CODE_ERROR_MALLOC);
	}
	(ptrarr->data)[ptrarr->len] = data;
	(ptrarr->len)++;
	return (CODE_OK);
}

void	ptrarr_free_all_ptr(t_ptrarr *ptrarr)
{
	int	i;

	i = 0;
	while (i < ptrarr->len)
	{
		free(ptrarr->data[i]);
		i++;
	}
}
