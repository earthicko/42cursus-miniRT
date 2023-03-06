/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:09:54 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:47 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_def.h"

int	ft_rand_r(unsigned long *seed)
{
	*seed = *seed * 1103515245 + 12345;
	return ((int)((*seed / 65536) % FT_RAND_MAX));
}

static void	ft_rand_processor(int mode, int *output, unsigned long seed)
{
	static int				initialized;
	static unsigned long	next;

	if (initialized == 0)
	{
		next = 1;
		initialized = 1;
	}
	if (mode == 0)
	{
		next = next * 1103515245 + 12345;
		*output = (int)((next / 65536) % FT_RAND_MAX);
	}
	else if (mode == 1)
		next = seed;
}

int	ft_rand(void)
{
	int	output;

	ft_rand_processor(0, &output, 0);
	return (output);
}

void	ft_srand(unsigned long seed)
{
	ft_rand_processor(1, 0, seed);
}
