/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 13:53:29 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:47 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	ft_nbrlen(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	ft_itoa_unsigned(int n, char *buf, int i)
{
	int	digit;
	int	divider;

	divider = 1;
	while (!(-10 < n / divider && n / divider < 10))
		divider *= 10;
	while (divider > 0)
	{
		digit = n / divider;
		n = n - (digit * divider);
		divider /= 10;
		if (digit < 0)
			digit = -digit;
		buf[i] = '0' + digit;
		i++;
	}
	buf[i] = '\0';
}

char	*ft_itoa(int n)
{
	char	*output;
	size_t	len;

	len = ft_nbrlen(n);
	output = malloc(sizeof(char) * (len + 1));
	if (!output)
		return (NULL);
	if (n < 0)
	{
		output[0] = '-';
		ft_itoa_unsigned(n, output, 1);
	}
	else
		ft_itoa_unsigned(n, output, 0);
	return (output);
}
