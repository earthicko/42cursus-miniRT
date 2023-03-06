/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_intarr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 13:54:11 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:51 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_intarr	*create_intarr(int cap)
{
	t_intarr	*arr;

	arr = malloc(sizeof(t_intarr));
	if (!arr)
		return (NULL);
	arr->data = malloc(sizeof(int) * cap);
	if (!arr->data)
	{
		free(arr);
		return (NULL);
	}
	arr->cap = cap;
	arr->len = 0;
	return (arr);
}

t_intarr	*del_intarr(t_intarr *arr)
{
	free(arr->data);
	free(arr);
	return (NULL);
}

int	realloc_intarr(t_intarr *arr, int new_cap)
{
	int	*new_data;
	int	copy_len;

	new_data = malloc(sizeof(int) * new_cap);
	if (!new_data)
		return (CODE_ERROR_MALLOC);
	copy_len = arr->len;
	if (new_cap < copy_len)
		copy_len = new_cap;
	ft_memcpy(new_data, arr->data, sizeof(int) * copy_len);
	arr->len = copy_len;
	arr->cap = new_cap;
	free(arr->data);
	arr->data = new_data;
	return (CODE_OK);
}

int	append_intarr(t_intarr *arr, int data)
{
	if (arr->cap == arr->len && realloc_intarr(arr, arr->cap * 2))
		return (CODE_ERROR_MALLOC);
	arr->data[arr->len] = data;
	arr->len++;
	return (CODE_OK);
}
