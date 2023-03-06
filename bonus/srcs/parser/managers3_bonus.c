/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   managers3_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle  <donghyle@student.42seoul.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:39:44 by donghyle          #+#    #+#             */
/*   Updated: 2023/03/06 22:39:44 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "parser_internal_bonus.h"

t_patternmatcher	setting_patternmatcher_manager(int i)
{
	static const t_patternmatcher	setting_matcher[N_IDENTIFIER_SETTING] = {
		is_setting_display,
		is_setting_camera,
		is_setting_renderer
	};

	if (i < 0 || i >= N_IDENTIFIER_SETTING)
		return (NULL);
	return (setting_matcher[i]);
}

t_builder	setting_builder_manager(int i)
{
	static const t_builder			setting_builder[N_IDENTIFIER_SETTING] = {
		build_setting_display,
		build_setting_camera,
		build_setting_renderer
	};

	if (i < 0 || i >= N_IDENTIFIER_SETTING)
		return (NULL);
	return (setting_builder[i]);
}
