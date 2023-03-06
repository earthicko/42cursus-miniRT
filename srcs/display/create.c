#include <stdlib.h>
#include "libft.h"
#include "display_internal.h"
#include "renderer.h"

t_display	*display_destroy(t_display *disp)
{
	if (disp->image)
		free(disp->image);
	if (disp->colors)
		free(disp->colors);
	free(disp);
	return (NULL);
}

t_display	*display_create(int width, int height, int multiplier)
{
	t_display	*disp;

	disp = malloc(sizeof(t_display));
	if (!disp)
		return (NULL);
	ft_bzero(disp, sizeof(t_display));
	disp->w = width;
	disp->h = height;
	disp->multiplier = multiplier;
	disp->w_real = width * multiplier;
	disp->h_real = height * multiplier;
	disp->ratio = (double)disp->w / (double)disp->h;
	disp->colors = malloc(sizeof(t_color) * width * height);
	if (!disp->colors)
		return (display_destroy(disp));
	disp->image = malloc(sizeof(t_uint) * width * height);
	if (!disp->image)
		return (display_destroy(disp));
	ft_bzero(disp->colors, sizeof(t_color) * width * height);
	ft_bzero(disp->image, sizeof(t_uint) * width * height);
	return (disp);
}
