NAME			= miniRT
################################# LIBRARIES ####################################
LIBFT_DIR		= libft
LIBFT			= $(LIBFT_DIR)/libft.a
LINK_LIBFT		= -L$(LIBFT_DIR)
INC_DIR_LIBFT	= -I$(LIBFT_DIR)/includes

LIBMLX_DIR		= minilibx_mms_20210621
LIBMLX_ORIG		= $(LIBMLX_DIR)/libmlx.dylib
LIBMLX			= ./libmlx.dylib
LINK_LIBMLX		= -L$(LIBMLX_DIR) -lmlx -framework OpenGL -framework AppKit
INC_DIR_LIBMLX	= -I$(LIBMLX_DIR)

LINK_LIBM		= -lm

LDLIBS			= $(LIBFT) $(LIBMLX)
LDFLAGS			= $(LINK_LIBFT) $(LINK_LIBMLX) $(LINK_LIBM)

INC_DIR			= -I. -Iincludes $(INC_DIR_LIBFT) $(INC_DIR_LIBMLX)
################################# COMMANDS #####################################
RM				= rm -rf
CFLAGS			= -Wall -Werror -Wextra -MMD -MP $(ACFLAGS) $(INC_DIR)
################################ FILENAMES #####################################
DIR_SRC			= srcs/
DIR_OBJ			= objs/
DIR_TEST_SRC	= tests/
DIR_TEST_OBJ	= test_objs/

FILENAME		= \
				geometry/matrix_init \
				geometry/matrix_inverse \
				geometry/matrix_inverse_utils \
				geometry/multiply \
				geometry/rotate \
				geometry/translate \
				geometry/vec_setval \
				geometry/vec3_add \
				geometry/vec3_cross \
				geometry/vec3_dot \
				geometry/vec3_mult \
				geometry/vec3_sub \
				geometry/vec3_reflect_refract \
				geometry/vec3_utils1 \
				geometry/vec3_utils2 \
				ray/utils \
				number/random \
				number/utils \
				ptrarr/create \
				ptrarr/getter \
				mlx_interface/create \
				mlx_interface/key_interface \
				mlx_interface/putpixel \
				mlx_interface/mlxman \
				camera/init \
				camera/get_ray_at \
				hittable/math_utils \
				hittable/hit_record_set_normal_and_face \
				hittable/sphere \
				hittable/plane \
				hittable/disk \
				hittable/tube \
				hittable/cylinder \
				hittable/list \
				material/diffuse_light \
				material/lambertian \
				material/methods \
				texture/solid \
				parser/parse_scene \
				parser/managers1 \
				parser/managers2 \
				parser/tokenizer \
				parser/get_tokentype \
				parser/parse_lines \
				parser/parse_lines_utils \
				parser/builder/add_resource \
				parser/builder/utils \
				parser/builder/checkrange \
				parser/builder/build_ambient_lighting \
				parser/builder/build_camera \
				parser/builder/build_light \
				parser/builder/build_sphere \
				parser/builder/build_plane \
				parser/builder/build_cylinder \
				scene/create \
				scene/destroy \
				renderer/init \
				renderer/render \
				renderer/render_pixel \
				renderer/write_color \

SRC				= $(addprefix $(DIR_SRC), $(addsuffix .c, $(FILENAME)))
OBJ				= $(addprefix $(DIR_OBJ), $(addsuffix .o, $(FILENAME)))
DEP				= $(addprefix $(DIR_OBJ), $(addsuffix .d, $(FILENAME)))

DRIVER_FILENAME	= main
DRIVER_SRC		= $(addprefix $(DIR_SRC), $(addsuffix .c, $(DRIVER_FILENAME)))
DRIVER_OBJ		= $(addprefix $(DIR_OBJ), $(addsuffix .o, $(DRIVER_FILENAME)))
DRIVER_DEP		= $(addprefix $(DIR_OBJ), $(addsuffix .d, $(DRIVER_FILENAME)))

################################# TARGETS ######################################
all: $(NAME)

$(DIR_OBJ)%.o: $(DIR_SRC)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC_DIR) -c -o $@ $<

$(DIR_TEST_OBJ)%.o: $(DIR_TEST_SRC)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC_DIR) -c -o $@ $<

$(NAME): $(OBJ) $(LDLIBS) $(DRIVER_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) $(DRIVER_OBJ) -o $@ $(LDFLAGS)

$(LIBFT):
	@make -j4 -C $(LIBFT_DIR)/

$(LIBMLX_ORIG):
	@make -C $(LIBMLX_DIR)/

$(LIBMLX): $(LIBMLX_ORIG)
	cp $(LIBMLX_ORIG) .

-include $(DEP)

clean:
	$(RM) $(DIR_OBJ) $(DIR_TEST_OBJ)
	$(RM) $(LIBMLX)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(LIBMLX_DIR)

fclean: clean
	$(RM) $(NAME) $(BONUS)
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(LIBMLX_DIR)

re:
	@make fclean
	@make all

.PHONY: all bonus clean fclean re
