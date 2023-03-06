/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 13:54:50 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:50 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

static void	ft_build_map(char const *set, int *map)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (i < UCHAR_MAX + 1)
		map[i++] = 0;
	len = ft_strlen(set);
	i = 0;
	while (i < len)
		map[((int)set[i++]) - CHAR_MIN] = 1;
}

static int	ft_is_in_map(char c, int *map)
{
	return (map[(int)c - CHAR_MIN]);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		map[UCHAR_MAX + 1];
	t_uint	i_start;
	t_uint	i_end;
	size_t	len;

	ft_build_map(set, map);
	i_start = 0;
	i_end = ft_strlen(s1);
	len = (size_t) i_end;
	while (i_start < len && ft_is_in_map(s1[i_start], map))
		i_start++;
	while (1 <= i_end && ft_is_in_map(s1[i_end - 1], map))
		i_end--;
	if (i_start < i_end)
		len = i_end - i_start;
	else
		len = 0;
	return (ft_substr(s1, i_start, len));
}

char	*ft_substr(char const *s, t_uint start, size_t len)
{
	size_t			len_s;
	char			*substr;

	len_s = ft_strlen(s);
	if ((size_t) start >= len_s)
		len = 0;
	else if (len_s - (size_t) start < len)
		len = len_s - (size_t) start;
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	ft_memcpy(substr, s + start, len);
	substr[len] = '\0';
	return (substr);
}
