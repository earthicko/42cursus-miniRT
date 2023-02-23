#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

int	main(void)
{
	parse_scene("./tests/test.rt");
	system("leaks test_parser");
	return (0);
}
