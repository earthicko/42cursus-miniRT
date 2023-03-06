#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "material.h"
#include "geometry.h"
#include "hittable_internal.h"

t_bool	hit_aa_box(t_hittable *hittable,
					const t_ray *ray,
					t_minmax t,
					t_hit_record *rec)
{
	t_hittable_aa_box	*this;

	this = (t_hittable_aa_box *)hittable;
	return (this->faces->hit(this->faces, ray, t, rec));
}

void	hittable_aa_box_destroy(t_hittable *self)
{
	t_hittable_aa_box		*this;
	t_hittable_list			*face_list;
	t_hittable_aa_rectangle	*face;
	int						i;

	this = (t_hittable_aa_box *)self;
	if (this->faces)
	{
		face_list = (t_hittable_list *)this->faces;
		i = 0;
		while (i < 6)
		{
			face = (t_hittable_aa_rectangle *)face_list->elements->data[i];
			face->destroy((t_hittable *)face);
			i++;
		}
		this->faces->destroy(this->faces);
	}
	free(this);
}

static void	set_aa_rect_info(t_aa_rectangle_info *aa_rect_info, int i,
				t_aa_box_info *info)
{
	const int	other_axises[3][2] = {{1, 2}, {2, 0}, {0, 1}};

	aa_rect_info->axis = i / 2;
	aa_rect_info->offset = info->widths[i / 2] / 2;
	aa_rect_info->flip = FALSE;
	if (i % 2)
	{
		aa_rect_info->offset = -aa_rect_info->offset;
		aa_rect_info->flip = TRUE;
	}
	aa_rect_info->range[0].min
		= -(info->widths[other_axises[i / 2][0]] / 2);
	aa_rect_info->range[0].max
		= +(info->widths[other_axises[i / 2][0]] / 2);
	aa_rect_info->range[1].min
		= -(info->widths[other_axises[i / 2][1]] / 2);
	aa_rect_info->range[1].max
		= +(info->widths[other_axises[i / 2][1]] / 2);
}

static int	add_faces(t_hittable *faces, t_aa_box_info *info)
{
	t_aa_rectangle_info	aa_rect_info;
	t_hittable			*face;
	int					i;

	i = 0;
	while (i < 6)
	{
		set_aa_rect_info(&aa_rect_info, i, info);
		face = hittable_aa_rectangle_create(aa_rect_info, info->mt[i]);
		if (!face)
			return (CODE_ERROR_MALLOC);
		if (hittable_list_append(faces, face))
			return (CODE_ERROR_MALLOC);
		i++;
	}
	return (CODE_OK);
}

t_hittable	*hittable_aa_box_create(t_aa_box_info *info)
{
	t_hittable_aa_box	*aa_box;

	aa_box = malloc(sizeof(t_hittable_aa_box));
	if (!aa_box)
		return (NULL);
	ft_memset(aa_box, 0, sizeof(t_hittable_aa_box));
	aa_box->destroy = hittable_aa_box_destroy;
	aa_box->hit = hit_aa_box;
	aa_box->faces = hittable_list_create();
	if (!aa_box->faces)
	{
		hittable_aa_box_destroy((t_hittable *)aa_box);
		return (NULL);
	}
	if (add_faces(aa_box->faces, info))
	{
		hittable_aa_box_destroy((t_hittable *)aa_box);
		return (NULL);
	}
	aa_box->bbox = ((t_hittable_list *)aa_box->faces)->bbox;
	return ((t_hittable *)aa_box);
}	
