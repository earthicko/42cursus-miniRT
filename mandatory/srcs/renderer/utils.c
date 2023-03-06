#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "renderer_internal.h"

char	*get_filename(int n)
{
	char	*filename;
	char	*postfix;

	postfix = ft_itoa(n);
	if (!postfix)
		return (NULL);
	filename = ft_strmerge(4, OUTPUT_FILENAME, "_", postfix, ".bmp");
	free(postfix);
	if (!filename)
		return (NULL);
	return (filename);
}

void	renderer_render_showstat(int n_samples)
{
	static int			i;
	const static char	*blinker[3] = {".     ", "..    ", "...   "};

	ft_printf("\rSample count %d ", n_samples);
	ft_printf("%s", blinker[(i++) % (sizeof(blinker) / sizeof(char *))]);
}
