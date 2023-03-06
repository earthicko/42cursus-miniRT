/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_ptrarr	*ptrarr_destroy(t_ptrarr *ptrarr, void (*destroyer)(void *))
{
	if (destroyer)
		ptrarr_destroy_all(ptrarr, destroyer);
	free(ptrarr->data);
	free(ptrarr);
	return (NULL);
}

int	ptrarr_expand(t_ptrarr *ptrarr)
{
	const void	**new_data;

	new_data = malloc(sizeof(const void *) * ptrarr->cap * 2);
	if (!new_data)
		return (CODE_ERROR_MALLOC);
	ft_memcpy(new_data, ptrarr->data, sizeof(void *) * ptrarr->len);
	free(ptrarr->data);
	ptrarr->data = new_data;
	ptrarr->cap = ptrarr->cap * 2;
	return (CODE_OK);
}

int	ptrarr_append(t_ptrarr *ptrarr, const void *data)
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

void	ptrarr_destroy_all(t_ptrarr *ptrarr, void (*destroyer)(void *))
{
	int	i;

	i = 0;
	while (i < ptrarr->len)
	{
		destroyer((void *)ptrarr->data[i]);
		i++;
	}
}
