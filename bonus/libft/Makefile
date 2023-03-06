NAME		= libft.a

INC_DIR		:= $(INC_DIR) -I./includes
CFLAGS		= -Wall -Werror -Wextra -MMD -MP $(ACFLAGS) $(INC_DIR)
ARFLAGS		= rcs

include filelist.mk

all: $(NAME)

$(NAME): $(OBJ_LIBFT)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ_LIBFT)

-include $(DEP_LIBFT)

clean:
	$(RM) $(OBJ_LIBFT) $(DEP_LIBFT)

fclean: clean
	$(RM) $(NAME)

re:
	@make fclean
	@make all

.PHONY: all clean fclean re
