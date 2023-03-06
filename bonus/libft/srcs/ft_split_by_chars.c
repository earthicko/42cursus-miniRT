/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_by_chars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 13:54:11 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:49 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "libft.h"

static void	skip_separator(char **start, int *map, int inverted)
{
	if (inverted)
	{
		while (**start != '\0' && !map[(t_uchar)**start])
			(*start)++;
	}
	else
	{
		while (**start != '\0' && map[(t_uchar)**start])
			(*start)++;
	}
}

static char	*ft_strcpy_word(char *str, int *map)
{
	int		len_word;
	int		idx;
	char	*word;

	idx = 0;
	len_word = 0;
	while (str[len_word] != '\0' && !map[(t_uchar)str[len_word]])
		len_word++;
	word = malloc(sizeof(char) * (len_word + 1));
	if (!word)
		return (NULL);
	while (idx < len_word)
	{
		word[idx] = str[idx];
		idx++;
	}
	word[idx] = '\0';
	return (word);
}

static int	init_split_by_chars(char *str, char *sep, int *map, char ***strs)
{
	int	i;
	int	n_words;

	i = 0;
	while (i < UCHAR_MAX)
	{
		map[i] = 0;
		i++;
	}
	while (*sep)
	{
		map[(t_uchar)(*sep)] = 1;
		sep++;
	}
	n_words = 0;
	while (*str != '\0')
	{
		skip_separator(&str, map, 0);
		if (*str != '\0')
			n_words++;
		skip_separator(&str, map, 1);
	}
	*strs = malloc(sizeof(char *) * (n_words + 1));
	return (n_words);
}

char	**ft_split_by_chars(char const *s, char *sep)
{
	int		is_sep[UCHAR_MAX];
	char	**strs;
	int		idx;
	int		n_words;
	char	*cursor;

	cursor = (char *)s;
	idx = 0;
	n_words = init_split_by_chars(cursor, sep, is_sep, &strs);
	if (!strs)
		return (NULL);
	ft_memset(strs, 0, sizeof(char *) * (n_words + 1));
	while (*cursor != '\0')
	{
		skip_separator(&cursor, is_sep, 0);
		if (*cursor != '\0')
		{
			strs[idx] = ft_strcpy_word(cursor, is_sep);
			if (!strs[idx])
				return (ft_free_strarr(strs));
			idx++;
		}
		skip_separator(&cursor, is_sep, 1);
	}
	return (strs);
}
