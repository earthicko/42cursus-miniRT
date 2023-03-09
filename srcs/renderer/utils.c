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
	static const char	*blinker[3] = {".     ", "..    ", "...   "};

	ft_printf("\rSample count %d ", n_samples);
	ft_printf("%s", blinker[(i++) % (sizeof(blinker) / sizeof(char *))]);
}

void	renderer_render_showstat_multithread(int n_samples, int worker_idx)
{
	static int			i;
	static const char	*blinker[3] = {".     ", "..    ", "...   "};

	ft_printf("\rWorker %d Sample count %d ", worker_idx, n_samples);
	ft_printf("%s", blinker[(i++) % (sizeof(blinker) / sizeof(char *))]);
}

int	get_next_milestone(t_renderer *renderer, int current_milestone)
{
	if (current_milestone == 1 && renderer->freq_update != 1)
		current_milestone = renderer->freq_update;
	else
		current_milestone += renderer->freq_update;
	if (current_milestone > renderer->max_samples)
		current_milestone = renderer->max_samples;
	return (current_milestone);
}
