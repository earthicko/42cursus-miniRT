/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:10:37 by donghyle          #+#    #+#             */
/*   Updated: 2022/07/08 12:10:39 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// contains: malloc, free, write, va_start, va_arg, va_copy, va_end
#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include "libft_def.h"

//			ft_rand
int			ft_rand(void);
int			ft_rand_r(unsigned long *seed);
void		ft_srand(unsigned long seed);
//			ft_asciitools
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isspace(char c);
int			ft_isprint(int c);
int			ft_iseol(char c);
int			ft_toupper(int c);
int			ft_tolower(int c);
//			ft_strtools
size_t		ft_strlen(const char *str);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strdup(const char *s1);
char		*ft_substr(char const *s, t_uint start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strmapi(char const *s, char (*f)(t_uint, char));
void		ft_striteri(char *s, void (*f)(t_uint, char*));
int			ft_strappend(char **body, const char *tail);
char		*ft_strmerge(int n_str, ...);
int			is_samestr(char *str1, char *str2);
//			ft_strarrtools
int			ft_strarrlen(char **strarr);
char		**ft_free_strarr(char **strarr);
//			ft_split
char		**ft_split(char const *s, char c);
char		**ft_split_by_chars(char const *s, char *sep);
//			ft_memtools
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_calloc(size_t count, size_t size);
void		*ft_realloc(void *ptr, size_t oldsize, size_t newsize);
void		ft_free(int n_ptr, ...);
//			str <-> int conversions
int			ft_atoi(const char *str);
double		ft_atof(const char *str);
int			ft_atoi_if_valid(const char *str, int *ret);
int			ft_atof_if_valid(const char *str, double *ret);
char		*ft_itoa(int n);
//			ft_put_fd
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
//			ft_lsttools
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void		ft_lstunlink(t_list **lst_head, t_list *lst, void (*del)(void *));
//			get_next_line
char		*get_next_line(int fd);
//			ft_printf
int			ft_printf(const char *format, ...);
int			ft_dprintf(int fd, const char *format, ...);
//			ft_print_error
void		ft_print_error(char *prefix, int code);
//			t_intarr
t_intarr	*create_intarr(int cap);
t_intarr	*del_intarr(t_intarr *arr);
int			realloc_intarr(t_intarr *arr, int new_cap);
int			append_intarr(t_intarr *arr, int data);
//			t_chararr
t_chararr	*create_chararr(int cap);
t_chararr	*del_chararr(t_chararr *arr);
int			realloc_chararr(t_chararr *arr, int new_cap);
int			append_chararr(t_chararr *arr, char data);
#endif
