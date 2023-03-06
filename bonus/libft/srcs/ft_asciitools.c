/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asciitools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:10:02 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:46 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (0 <= c && c < 128)
		return (1);
	return (0);
}

int	ft_tolower(int c)
{
	if ('A' <= c && c <= 'Z')
		c += ('a' - 'A');
	return (c);
}

int	ft_toupper(int c)
{
	if ('a' <= c && c <= 'z')
		c += ('A' - 'a');
	return (c);
}

int	ft_iseol(char c)
{
	return (c == '\0' || c == '\n');
}
