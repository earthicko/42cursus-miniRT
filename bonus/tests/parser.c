#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

int	main(void)
{
	t_scene	scene;

	parse_scene("./tests/test.rt", &scene);
	system("leaks test_parser");
	return (0);
}
