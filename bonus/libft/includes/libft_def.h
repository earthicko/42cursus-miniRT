/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_def.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:10:37 by donghyle          #+#    #+#             */
/*   Updated: 2022/07/08 12:10:39 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_DEF_H
# define LIBFT_DEF_H

# define FT_RAND_MAX 32767

enum	e_bool
{
	FALSE = 0,
	TRUE
};

enum	e_returncode
{
	CODE_OK = 0,
	CODE_ERROR_GENERIC = -1,
	CODE_ERROR_IO = -2,
	CODE_ERROR_MALLOC = -3,
	CODE_ERROR_SCOPE = -4,
	CODE_ERROR_DATA = -5
};

typedef int					t_bool;
typedef long long			t_ll;
typedef unsigned long long	t_ull;
typedef unsigned int		t_uint;
typedef unsigned char		t_uchar;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_intarr
{
	int	*data;
	int	cap;
	int	len;
}	t_intarr;

typedef struct s_chararr
{
	char	*data;
	int		cap;
	int		len;
}	t_chararr;

#endif
