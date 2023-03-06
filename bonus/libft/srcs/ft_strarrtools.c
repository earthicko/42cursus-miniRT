/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrtools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 13:54:11 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:50 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	ft_strarrlen(char **strarr)
{
	int	i;

	i = 0;
	while (strarr[i])
		i++;
	return (i);
}

char	**ft_free_strarr(char **strarr)
{
	char	**cursor;

	cursor = strarr;
	while (*cursor)
		free(*(cursor++));
	free(strarr);
	return (NULL);
}
