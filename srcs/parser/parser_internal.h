#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include "libft_def.h"
# include "ptrarr.h"
# include "scene.h"

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

typedef t_bool		(*t_wordtester)(const char *word);
typedef t_bool		(*t_patternmatcher)(const t_ptrarr *tokens);
typedef int			(*t_builder)(const t_ptrarr *tokens, t_scene *scene);

char				*tokenname_manager(int i);
t_wordtester		wordtester_manager(int i);
t_patternmatcher	unique_patternmatcher_manager(int i);
t_builder			unique_builder_manager(int i);
t_patternmatcher	common_patternmatcher_manager(int i);
t_builder			common_builder_manager(int i);

t_ptrarr			*tokenize(const char *line);
void				print_tokens(const t_ptrarr *tokens);
t_bool				is_identifier(const char *word);
t_bool				is_number(const char *word);
t_bool				is_comma(const char *word);
t_bool				is_in_pattern(
						const char *identifier,
						const int *pattern,
						const int patternlen,
						const t_ptrarr *tokens);

int					parse_line(
						const char *line,
						t_scene *scene,
						t_patternmatcher tester,
						t_builder builder);
int					parse_entities(const t_ptrarr *lines, t_scene *scene);

t_bool				is_ambient_lighting(const t_ptrarr *tokens);
t_bool				is_camera(const t_ptrarr *tokens);
t_bool				is_light(const t_ptrarr *tokens);
t_bool				is_sphere(const t_ptrarr *tokens);
t_bool				is_plane(const t_ptrarr *tokens);
t_bool				is_cylinder(const t_ptrarr *tokens);

void				parse_vector(t_vec3 *out, const void **token_start);

int					build_ambient_lighting(
						const t_ptrarr *tokens, t_scene *scene);
int					build_camera(
						const t_ptrarr *tokens, t_scene *scene);
int					build_light(
						const t_ptrarr *tokens, t_scene *scene);
int					build_sphere(
						const t_ptrarr *tokens, t_scene *scene);
int					build_plane(
						const t_ptrarr *tokens, t_scene *scene);
int					build_cylinder(
						const t_ptrarr *tokens, t_scene *scene);

#endif
