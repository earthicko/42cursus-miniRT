#include <stdio.h>
#include "print.h"
#include "mlx_interface.h"

int	main(void)
{
	t_display		*disp;
	t_imgwrapper	*img;
	t_color			color;
	t_uv			uv;

	disp = display_create(1, 1, 1, "");
	img = imgwrapper_create(disp, "tests/steve_head_front.xpm");
	printf("%p\n", img);
	vec2_setval(&uv, 1, 1);
	imgwrapper_getcolor(img, &color, &uv);
	printf("color at ");
	print_vec2(&uv);
	printf(" = ");
	print_vec3(&color);
	printf("\n");
	return (0);
}
