/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 13:48:26 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:47 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_number(const char *str)
{
	while (*str != '\0' && ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		str++;
	if (!ft_isdigit(*str))
		return (0);
	while (*str != '\0' && ft_isdigit(*str))
		str++;
	if (*str != '\0')
		return (0);
	return (1);
}

static void	init_ft_atoi_strict(const char **cursor, int *sign)
{
	while (**cursor != '\0' && ft_isspace(**cursor))
		(*cursor)++;
	*sign = 1;
	if (**cursor == '+' || **cursor == '-')
	{
		if (**cursor == '-')
			*sign = -1;
		(*cursor)++;
	}
}

static int	ft_atoi_strict(const char *str, int *ret)
{
	int		nbr;
	int		nbr_prev;
	int		sign;

	nbr = 0;
	nbr_prev = 0;
	init_ft_atoi_strict(&str, &sign);
	while (*str != '\0' && ft_isdigit(*str))
	{
		nbr = nbr_prev * 10 + sign * ((int)(*str - '0'));
		if (sign == 1 && nbr < nbr_prev)
			return (CODE_ERROR_GENERIC);
		if (sign == -1 && nbr > nbr_prev)
			return (CODE_ERROR_GENERIC);
		nbr_prev = nbr;
		str++;
	}
	*ret = nbr;
	return (CODE_OK);
}

int	ft_atoi_if_valid(const char *str, int *ret)
{
	if (!is_number(str))
		return (CODE_ERROR_GENERIC);
	return (ft_atoi_strict(str, ret));
}

int	ft_atoi(const char *str)
{
	long	output;
	long	sign;

	output = 0;
	while (*str != '\0' && ft_isspace(*str))
		str++;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str != '\0' && ft_isdigit(*str))
	{
		output = output * 10 + ((long)(*str - '0'));
		str++;
	}
	output *= sign;
	return ((int) output);
}
