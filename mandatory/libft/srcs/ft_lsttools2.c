/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttools2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 14:27:02 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:47 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*cursor;

	head = NULL;
	while (lst != NULL)
	{
		cursor = ft_lstnew(f(lst->content));
		if (!cursor)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		ft_lstadd_back(&head, cursor);
		lst = lst->next;
	}
	return (head);
}

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

t_list	*ft_lstlast(t_list *lst)
{
	while (lst != NULL && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstunlink(t_list **lst_head, t_list *lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*prev;

	if (*lst_head == lst)
	{
		temp = (*lst_head)->next;
		ft_lstdelone(*lst_head, del);
		*lst_head = temp;
		return ;
	}
	prev = *lst_head;
	while (prev->next)
	{
		if (prev->next == lst)
		{
			temp = prev->next;
			prev->next = prev->next->next;
			ft_lstdelone(temp, del);
			return ;
		}
		prev = prev->next;
	}
}
