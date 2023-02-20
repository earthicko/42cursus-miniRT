NAME			= miniRT
################################# LIBRARIES ####################################
LIBFT_DIR		= libft
LIBFT			= $(LIBFT_DIR)/libft.a
LINK_LIBFT		= -L$(LIBFT_DIR)
INC_DIR_LIBFT	= -I$(LIBFT_DIR)/includes

LDLIBS			= $(LIBFT)
LDFLAGS			= $(LINK_LIBFT)

INC_DIR			= -I. -Iincludes $(INC_DIR_LIBFT)
################################# COMMANDS #####################################
CFLAGS			= -Wall -Werror -Wextra -MMD -MP $(ACFLAGS) $(INC_DIR)
################################ FILENAMES #####################################
DRIVER_FILENAME	= main
DRIVER_SRC		= $(addprefix srcs/, $(addsuffix .c, $(DRIVER_FILENAME)))
DRIVER_OBJ		= $(addprefix srcs/, $(addsuffix .o, $(DRIVER_FILENAME)))
DRIVER_DEP		= $(addprefix srcs/, $(addsuffix .d, $(DRIVER_FILENAME)))

FILENAME		= \
				geometry/matrix_init \
				geometry/multiply \
				geometry/rotate \
				geometry/translate

SRC				= $(addprefix srcs/, $(addsuffix .c, $(FILENAME)))
OBJ				= $(addprefix srcs/, $(addsuffix .o, $(FILENAME)))
DEP				= $(addprefix srcs/, $(addsuffix .d, $(FILENAME)))
################################# TARGETS ######################################
all: $(NAME)

$(NAME): $(LDLIBS) $(OBJ) $(DRIVER_OBJ)
	$(CC) $(CFLAGS) $(LDLIBS) $(OBJ) $(DRIVER_OBJ) -o $@ $(LDFLAGS)

$(LIBFT):
	@make -j4 -C $(LIBFT_DIR)/

-include $(DEP)

clean:
	$(RM) $(OBJ) $(DEP) $(DRIVER_OBJ) $(DRIVER_DEP)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME) $(BONUS)
	@make fclean -C $(LIBFT_DIR)

re:
	@make fclean
	@make all

.PHONY: all bonus clean fclean re
