/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ptrarr_bonus.h"
#include "hittable_internal_bonus.h"

t_bool	hittable_list_hit(t_hittable *self,
			const t_ray *r, t_minmax t, t_hit_record *rec)
{
	t_hittable_list	*this;
	t_hittable		*element;
	t_bool			hit_anything;
	t_hit_record	rec_buf;
	int				i;

	this = (t_hittable_list *)self;
	if (hittable_has_bbox(self) && !this->bbox.hit(&this->bbox, r, &t))
		return (FALSE);
	hit_anything = FALSE;
	i = 0;
	while (i < this->elements->len)
	{
		element = (t_hittable *)this->elements->data[i];
		if (element->hit(element, r, t, &rec_buf))
		{
			hit_anything = TRUE;
			*rec = rec_buf;
			t.max = rec_buf.t;
		}
		i++;
	}
	return (hit_anything);
}

void	hittable_list_update_bbox(t_hittable *self)
{
	t_hittable_list	*this;
	int				i;

	this = (t_hittable_list *)self;
	if (this->elements->len == 0)
	{
		ft_bzero(&self->bbox, sizeof(t_bbox));
		return ;
	}
	this->bbox = ((t_hittable *)ptrarr_get(this->elements, 0))->bbox;
	i = 1;
	while (i < this->elements->len)
	{
		bbox_init_surrounding(&this->bbox, &this->bbox,
			&((t_hittable *)ptrarr_get(this->elements, i))->bbox);
		i++;
	}
}

int	hittable_list_append(t_hittable *self, t_hittable *item)
{
	t_hittable_list	*this;
	int				stat;

	this = (t_hittable_list *)self;
	stat = ptrarr_append(this->elements, item);
	if (stat == CODE_OK)
		hittable_list_update_bbox(self);
	return (stat);
}

void	hittable_list_destroy(t_hittable *self)
{
	ptrarr_destroy(((t_hittable_list *)self)->elements, NULL);
	free(self);
}

t_hittable	*hittable_list_create(void)
{
	t_hittable_list	*list;

	list = malloc(sizeof(t_hittable_list));
	if (!list)
		return (NULL);
	ft_bzero(list, sizeof(t_hittable_list));
	list->destroy = hittable_list_destroy;
	list->hit = hittable_list_hit;
	list->elements = ptrarr_create();
	if (!list->elements)
	{
		free(list);
		return (NULL);
	}
	return ((t_hittable *)list);
}
