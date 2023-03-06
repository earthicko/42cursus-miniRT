/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:14:25 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:48 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_error(char *prefix, int code)
{
	char	*msg[6];

	if (code >= CODE_OK || CODE_ERROR_DATA > code)
		return ;
	msg[-CODE_ERROR_GENERIC] = "%sUnknown error.\n";
	msg[-CODE_ERROR_IO] = "%sI/O Error.\n";
	msg[-CODE_ERROR_MALLOC] = "%sCannot allocate memory.\n";
	msg[-CODE_ERROR_SCOPE] = "%sValue is out of scope.\n";
	msg[-CODE_ERROR_DATA] = "%sInvalid data.\n";
	ft_dprintf(2, msg[-code], prefix);
}
