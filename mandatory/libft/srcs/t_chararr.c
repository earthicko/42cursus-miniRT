/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_chararr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 13:54:11 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:51 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_chararr	*create_chararr(int cap)
{
	t_chararr	*arr;

	arr = malloc(sizeof(t_chararr));
	if (!arr)
		return (NULL);
	arr->data = malloc(sizeof(char) * cap);
	if (!arr->data)
	{
		free(arr);
		return (NULL);
	}
	arr->cap = cap;
	arr->len = 0;
	return (arr);
}

t_chararr	*del_chararr(t_chararr *arr)
{
	free(arr->data);
	free(arr);
	return (NULL);
}

int	realloc_chararr(t_chararr *arr, int new_cap)
{
	char	*new_data;
	int		copy_len;

	new_data = malloc(sizeof(char) * new_cap);
	if (!new_data)
		return (CODE_ERROR_MALLOC);
	copy_len = arr->len;
	if (new_cap < copy_len)
		copy_len = new_cap;
	ft_memcpy(new_data, arr->data, sizeof(char) * copy_len);
	arr->len = copy_len;
	arr->cap = new_cap;
	free(arr->data);
	arr->data = new_data;
	return (CODE_OK);
}

int	append_chararr(t_chararr *arr, char data)
{
	if (arr->cap == arr->len && realloc_chararr(arr, arr->cap * 2))
		return (CODE_ERROR_MALLOC);
	arr->data[arr->len] = data;
	arr->len++;
	return (CODE_OK);
}
