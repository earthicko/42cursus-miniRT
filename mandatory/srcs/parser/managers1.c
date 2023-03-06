/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   managers1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "parser_internal.h"

char	*tokenname_manager(int i)
{
	static const char	*names[N_IDENTIFIER] = {
		IDENTIFIER_AMBIENTLIGHTING,
		IDENTIFIER_CAMERA,
		IDENTIFIER_LIGHT,
		IDENTIFIER_SPHERE,
		IDENTIFIER_PLANE,
		IDENTIFIER_CYLINDER,
	};

	if (i < 0 || i >= N_IDENTIFIER)
		return (NULL);
	return ((char *)names[i]);
}

t_wordtester	wordtester_manager(int i)
{
	static const t_wordtester	testers[4] = {
		is_identifier,
		is_number,
		is_comma,
		is_word
	};

	if (i < 0 || i >= N_TOKENTYPE)
		return (NULL);
	return (testers[i]);
}
