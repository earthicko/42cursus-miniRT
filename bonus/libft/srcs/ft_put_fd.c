/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 13:53:55 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:49 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	while (*s != '\0')
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

static void	ft_putnbr_unsigned_fd(int n, int fd)
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
		ft_putchar_fd(digit + '0', fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
		write(fd, "-", 1);
	ft_putnbr_unsigned_fd(n, fd);
}
