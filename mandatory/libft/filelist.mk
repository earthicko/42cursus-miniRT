FILE_LIBFT	= \
			ft_rand \
			ft_asciitools \
			ft_asciitools2 \
			ft_memtools \
			ft_memtools2 \
			ft_memtools3 \
			ft_strtools \
			ft_strtools2 \
			ft_strtools3 \
			ft_strtools4 \
			ft_strarrtools \
			ft_split \
			ft_split_by_chars \
			ft_atoi \
			ft_atof \
			ft_atof_if_valid \
			ft_itoa \
			ft_put_fd \
			ft_lsttools \
			ft_lsttools2 \
			ft_free \
			get_next_line \
			get_next_line_utils \
			ft_printf \
			ft_printf_t_conv \
			ft_printf_parse_format \
			ft_printf_parse_format_utils \
			ft_printf_create_str \
			ft_printf_create_str_utils \
			ft_printf_fwrite_chr \
			ft_printf_fwrite_num \
			ft_printf_fwrite_ptr \
			ft_printf_fwrite_utils \
			ft_print_error \
			t_intarr \
			t_chararr

SRC_LIBFT	= $(addprefix srcs/, $(addsuffix .c, $(FILE_LIBFT)))
OBJ_LIBFT	= $(addprefix srcs/, $(addsuffix .o, $(FILE_LIBFT)))
DEP_LIBFT	= $(addprefix srcs/, $(addsuffix .d, $(FILE_LIBFT)))
