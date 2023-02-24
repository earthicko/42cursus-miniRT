#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include "libft_def.h"
# include "ptrarr.h"

# define PARSER_DELIMETER ' '
# define PARSER_COMMA ','
# define PARSER_COMMA_STR ","
# define N_IDENTIFIER			6
# define N_IDENTIFIER_UNIQUE	3
# define N_IDENTIFIER_COMMON	3
# define IDENTIFIER_AMBIENTLIGHTING	"A"
# define IDENTIFIER_CAMERA			"C"
# define IDENTIFIER_LIGHT			"L"
# define IDENTIFIER_SPHERE			"sp"
# define IDENTIFIER_PLANE			"pl"
# define IDENTIFIER_CYLINDER		"cy"
# define IDENTIFIER_NAME_AMBIENTLIGHTING	"Ambient Lighting"
# define IDENTIFIER_NAME_CAMERA				"Camera"
# define IDENTIFIER_NAME_LIGHT				"Light"
# define IDENTIFIER_NAME_SPHERE				"Sphere"
# define IDENTIFIER_NAME_PLANE				"Plane"
# define IDENTIFIER_NAME_CYLINDER			"Cylinder"
# define N_TOKENTYPE 3

typedef enum e_tokentype
{
	TOKENTYPE_IDENTIFIER = 0,
	TOKENTYPE_NUMBER,
	TOKENTYPE_COMMA
}	t_tokentype;

typedef t_bool		(*t_wordtester)(char *word);
typedef t_bool		(*t_patternmatcher)(t_ptrarr *tokens);
typedef int			(*t_builder)(char *line);

char				*tokenname_manager(int i);
t_wordtester		wordtester_manager(int i);
t_patternmatcher	unique_patternmatcher_manager(int i);
t_builder			unique_builder_manager(int i);
t_patternmatcher	common_patternmatcher_manager(int i);
t_builder			common_builder_manager(int i);

t_ptrarr			*tokenize(char *line);
void				print_tokens(t_ptrarr *tokens);
t_bool				is_identifier(char *word);
t_bool				is_number(char *word);
t_bool				is_comma(char *word);
t_bool				is_in_pattern(
						const char *identifier,
						const int *pattern,
						const int patternlen,
						t_ptrarr *tokens);

int					parse_line(
						char *line,
						t_patternmatcher tester,
						t_builder builder);
int					parse_entities(t_ptrarr *lines);

t_bool				is_ambient_lighting(t_ptrarr *tokens);
t_bool				is_camera(t_ptrarr *tokens);
t_bool				is_light(t_ptrarr *tokens);
t_bool				is_sphere(t_ptrarr *tokens);
t_bool				is_plane(t_ptrarr *tokens);
t_bool				is_cylinder(t_ptrarr *tokens);

int					build_ambient_lighting(char *line);
int					build_camera(char *line);
int					build_light(char *line);
int					build_sphere(char *line);
int					build_plane(char *line);
int					build_cylinder(char *line);

#endif
