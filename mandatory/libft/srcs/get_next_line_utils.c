/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:08:47 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:51 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"
#include "libft.h"

t_fdbuff	*init_fdbuff(int fd)
{
	t_fdbuff	*fdbuff;

	fdbuff = malloc(sizeof(t_fdbuff));
	if (!fdbuff)
		return (NULL);
	fdbuff->fd = fd;
	fdbuff->buff = NULL;
	return (fdbuff);
}

void	del_fdbuff(void *fdbuff)
{
	free(((t_fdbuff *)fdbuff)->buff);
	free((t_fdbuff *)fdbuff);
}

t_list	*init_fdlist(t_list **head, int init_fd)
{
	t_list	*init;

	init = malloc(sizeof(t_list));
	if (!init)
		return (NULL);
	init->content = init_fdbuff(init_fd);
	if (!init->content)
	{
		free(init);
		return (NULL);
	}
	init->next = *head;
	*head = init;
	return (init);
}

void	*del_fdlist(t_list **buff_list, t_list *target)
{
	t_list	*cursor;
	t_list	*prev;

	if (*buff_list == target)
	{
		*buff_list = target->next;
		ft_lstdelone(target, del_fdbuff);
		return (NULL);
	}
	cursor = (*buff_list)->next;
	prev = *buff_list;
	while (cursor != NULL)
	{
		if (cursor == target)
		{
			prev->next = cursor->next;
			ft_lstdelone(cursor, del_fdbuff);
			return (NULL);
		}
		cursor = cursor->next;
		prev = prev->next;
	}
	return (NULL);
}

t_fdbuff	*loc_fdbuff(t_list *node)
{
	return ((t_fdbuff *)node->content);
}
