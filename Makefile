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

TEST_FILENAME	= \
				vectors_arithmetic \
				print0
TEST_SRC		= $(addprefix tests/, $(addsuffix .c, $(TEST_FILENAME)))
TEST_OBJ		= $(addprefix tests/, $(addsuffix .o, $(TEST_FILENAME)))
TEST_DEP		= $(addprefix tests/, $(addsuffix .d, $(TEST_FILENAME)))

TESTER_FILENAME	= \
				vectors \
				camera \
				texture
TESTER_SRC		= $(addprefix tests/, $(addsuffix .c, $(TESTER_FILENAME)))
TESTER_OBJ		= $(addprefix tests/, $(addsuffix .o, $(TESTER_FILENAME)))
TESTER_DEP		= $(addprefix tests/, $(addsuffix .d, $(TESTER_FILENAME)))

FILENAME		= \
				geometry/matrix_init \
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
				number/random \
				number/degree \
				ptrarr/ptrarr \
				camera/camera_init \
				camera/camera_get_ray_at \
				material/material_diffuse_light \
				material/material_metal \
				material/material_dielectric \
				material/material_lambertian \
				material/material \
				texture/texture_solid

SRC				= $(addprefix srcs/, $(addsuffix .c, $(FILENAME)))
OBJ				= $(addprefix srcs/, $(addsuffix .o, $(FILENAME)))
DEP				= $(addprefix srcs/, $(addsuffix .d, $(FILENAME)))
################################# TARGETS ######################################
all: $(NAME)

$(NAME): $(LDLIBS) $(OBJ) $(DRIVER_OBJ)
	$(CC) $(CFLAGS) $(LDLIBS) $(OBJ) $(DRIVER_OBJ) -o $@ $(LDFLAGS)

$(LIBFT):
	@make -j4 -C $(LIBFT_DIR)/

test_vectors: tests/vectors.o $(LDLIBS) $(OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(LDLIBS) $(OBJ) $(TEST_OBJ) tests/vectors.o -o $@ $(LDFLAGS)

test_camera: tests/camera.o $(LDLIBS) $(OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(LDLIBS) $(OBJ) $(TEST_OBJ) tests/camera.o -o $@ $(LDFLAGS)

test_texture: tests/texture.o $(LDLIBS) $(OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(LDLIBS) $(OBJ) $(TEST_OBJ) tests/texture.o -o $@ $(LDFLAGS)

test_material: tests/material.o $(LDLIBS) $(OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(LDLIBS) $(OBJ) $(TEST_OBJ) tests/material.o -o $@ $(LDFLAGS)

-include $(DEP)

clean:
	$(RM) $(OBJ) $(DEP) $(DRIVER_OBJ) $(DRIVER_DEP)
	$(RM) $(TEST_OBJ) $(TEST_DEP) $(TESTER_OBJ) $(TESTER_DEP)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME) $(BONUS)
	$(RM) test_vectors test_camera test_texture test_material
	@make fclean -C $(LIBFT_DIR)

re:
	@make fclean
	@make all

.PHONY: all bonus clean fclean re
