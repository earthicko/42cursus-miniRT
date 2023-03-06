/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:10:37 by donghyle          #+#    #+#             */
/*   Updated: 2022/07/08 12:10:39 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft_def.h"
# include "ft_printf_def.h"

//			ft_printf.c
int			ft_printf(const char *format, ...);
//			create_str.c
char		*cstr_nchars(int n, char c);
char		*cstr_nbr(t_conv *conv, t_ll nbr, char *charset);
char		*cstr_prefix(t_conv *conv, t_ll num, t_ll base);
char		*cstr_padding(t_conv *conv, int len_rest);
//			create_str_utils.c
int			ft_numlen_base(t_ll num, t_ll base);
int			cstr_nbr_fill_str(char *buf, t_ll nbr, char *base, int l_base);
char		*cstr_sign(t_conv *conv, t_ll num);
int			append_hex_prefix(t_conv *conv, t_ll num, t_ll base, char **buf);
int			append_precision(t_conv *conv, t_ll num, t_ll base, char **buf);
//			ft_str_utils.c
int			ft_strappend(char **body, const char *tail);
char		*ft_strmerge(int n_str, ...);
//			fwrite_chr.c
int			fwrite_plain(int fd, t_conv *conv);
int			fwrite_char(int fd, t_conv *conv, int c);
int			fwrite_str(int fd, t_conv *conv, char *str);
//			fwrite_num.c
int			fwrite_int(int fd, t_conv *conv, int num, char *charset);
int			fwrite_uint(int fd, t_conv *conv, t_uint num, char *charset);
//			fwrite_ptr.c
int			fwrite_ptr(int fd, t_conv *conv, void *ptr);
//			fwrite_utils.c
char		*merge_num_buffers(t_conv *conv, char **buf);
void		abort_fwrite(char **bufs);
int			add_padding(t_conv *conv, char **buf);
//			parse_format.c
int			parse_format(t_list **convs, const char *format);
//			parse_format_utils.c
void		parse_printf_flags(t_conv *conv, char **format);
void		parse_printf_minwidth(t_conv *conv, char **format);
void		parse_printf_precision(t_conv *conv, char **format);
int			parse_printf_conv(t_conv *conv, char **fmt);
//			t_conv.c
t_conv		*create_conv(void);
void		del_conv(void *conv);
#endif
