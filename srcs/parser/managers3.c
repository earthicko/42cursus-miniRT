#include <stddef.h>
#include "parser_internal.h"

// TODO: add pointers to patternmatchers when they're ready
t_patternmatcher	setting_patternmatcher_manager(int i)
{
	static const t_patternmatcher	setting_matcher[N_IDENTIFIER_SETTING] = {
		0
	};

	if (i < 0 || i >= N_IDENTIFIER_SETTING)
		return (NULL);
	return (setting_matcher[i]);
}

// TODO: add pointers to builders when they're ready
t_builder	setting_builder_manager(int i)
{
	static const t_builder			setting_builder[N_IDENTIFIER_SETTING] = {
		0
	};

	if (i < 0 || i >= N_IDENTIFIER_SETTING)
		return (NULL);
	return (setting_builder[i]);
}
