#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include "libft_def.h"
# include "ptrarr.h"
# include "scene.h"
# include "builder/builder_internal.h"
# include "settingman.h"

# define PARSER_DELIMETER	' '
# define PARSER_COMMA		','
# define PARSER_COMMA_STR	","
# define PARSER_COMMENT		'#'
# define RANGE_MIN_RATIO	0.0
# define RANGE_MAX_RATIO	1.0
# define RANGE_MIN_FOV		0.0
# define RANGE_MAX_FOV		180.0
# define RANGE_MIN_COLOR	0.0
# define RANGE_MAX_COLOR	256.0
# define E_NORMALIZEDVEC3	1e-3
# define N_IDENTIFIER			15
# define N_IDENTIFIER_SETTING	3
# define N_IDENTIFIER_UNIQUE	2
# define N_IDENTIFIER_COMMON	10
# define IDENTIFIER_SETTING_DISPLAY		"display"
# define IDENTIFIER_SETTING_CAMERA		"camera"
# define IDENTIFIER_SETTING_RENDERER	"renderer"
# define IDENTIFIER_AMBIENTLIGHTING		"A"
# define IDENTIFIER_CAMERA				"C"
# define IDENTIFIER_LIGHT				"l"
# define IDENTIFIER_SPHERE				"sp"
# define IDENTIFIER_PLANE				"pl"
# define IDENTIFIER_CYLINDER			"cy"
# define IDENTIFIER_CONE				"co"
# define IDENTIFIER_TEXTURE_SOLID		"tx_solid"
# define IDENTIFIER_TEXTURE_CHECKER		"tx_checker"
# define IDENTIFIER_MATERIAL_LAMBERTIAN	"mt_lambertian"
# define IDENTIFIER_MATERIAL_METAL		"mt_metal"
# define IDENTIFIER_MATERIAL_DIELECTRIC	"mt_dielectric"
# define N_TOKENTYPE 4

typedef enum e_tokentype
{
	TOKENTYPE_IDENTIFIER = 0,
	TOKENTYPE_NUMBER,
	TOKENTYPE_COMMA,
	TOKENTYPE_WORD
}	t_tokentype;

typedef t_bool		(*t_wordtester)(const char *word);
typedef t_bool		(*t_patternmatcher)(const t_ptrarr *tokens);
typedef int			(*t_builder)(const t_ptrarr *tokens, t_scene *scene);

char				*tokenname_manager(int i);
t_wordtester		wordtester_manager(int i);
t_patternmatcher	setting_patternmatcher_manager(int i);
t_builder			setting_builder_manager(int i);
t_patternmatcher	unique_patternmatcher_manager(int i);
t_builder			unique_builder_manager(int i);
t_patternmatcher	common_patternmatcher_manager(int i);
t_builder			common_builder_manager(int i);

t_ptrarr			*tokenize(const char *line);
void				print_tokens(const t_ptrarr *tokens);
t_bool				is_identifier(const char *word);
t_bool				is_number(const char *word);
t_bool				is_comma(const char *word);
t_bool				is_word(const char *word);
t_bool				is_in_pattern(
						const char *identifier,
						const int *pattern,
						const int patternlen,
						const t_ptrarr *tokens);

t_ptrarr			*read_file_to_strarr(const char *path);
void				destroy_pchar(void *pchar);
int					parse_line(
						const char *line,
						t_scene *scene,
						t_patternmatcher tester,
						t_builder builder);
int					parse_lines(const t_ptrarr *lines, t_scene *scene);
int					parse_setting_loop(const char *line, t_scene *scene);

#endif
