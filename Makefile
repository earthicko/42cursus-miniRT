NAME			= miniRT
################################# LIBRARIES ####################################
LIBFT_DIR		= libft
LIBFT			= $(LIBFT_DIR)/libft.a
LINK_LIBFT		= -L$(LIBFT_DIR)
INC_DIR_LIBFT	= -I$(LIBFT_DIR)/includes

LINK_LIBM		= -lm

LDLIBS			= $(LIBFT)
LDFLAGS			= $(LINK_LIBFT) $(LINK_LIBM)

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

TEST_SRC		= $(addprefix tests/, $(addsuffix .c, $(TEST_FILENAME)))
TEST_OBJ		= $(addprefix tests/, $(addsuffix .o, $(TEST_FILENAME)))
TEST_DEP		= $(addprefix tests/, $(addsuffix .d, $(TEST_FILENAME)))

TESTER_FILENAME	= \
				vectors \
				camera \
				hittable \
				texture \
				material \
				parser \

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
				ray \
				number/random \
				number/degree \
				ptrarr/ptrarr \
				print/print0 \
				camera/camera_init \
				camera/camera_get_ray_at \
				hittable/math_utils \
				hittable/hit_record_set_normal_and_face \
				hittable/sphere \
				material/material_diffuse_light \
				material/material_metal \
				material/material_dielectric \
				material/material_lambertian \
				material/material \
				texture/texture_solid \
				texture/texture_checker \
				parser/parser \
				parser/parser_managers1 \
				parser/parser_managers2 \
				parser/parser_tokenizer \
				parser/parser_get_tokentype \
				parser/parser_entities/parser_entities \
				parser/parser_entities/parser_utils \
				parser/parser_entities/parser_ambient_lighting \
				parser/parser_entities/parser_camera \
				parser/parser_entities/parser_light \
				parser/parser_entities/parser_sphere \
				parser/parser_entities/parser_plane \
				parser/parser_entities/parser_cylinder \

SRC				= $(addprefix srcs/, $(addsuffix .c, $(FILENAME)))
OBJ				= $(addprefix srcs/, $(addsuffix .o, $(FILENAME)))
DEP				= $(addprefix srcs/, $(addsuffix .d, $(FILENAME)))
################################# TARGETS ######################################
all: $(NAME)

$(NAME): $(OBJ) $(LDLIBS) $(DRIVER_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) $(DRIVER_OBJ) -o $@ $(LDFLAGS)

$(LIBFT):
	@make -j4 -C $(LIBFT_DIR)/

test_vectors: tests/vectors.o $(OBJ) $(LDLIBS) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) $(TEST_OBJ) tests/vectors.o -o $@ $(LDFLAGS)

test_camera: tests/camera.o $(OBJ) $(LDLIBS) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) $(TEST_OBJ) tests/camera.o -o $@ $(LDFLAGS)

test_texture: tests/texture.o $(OBJ) $(LDLIBS) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) $(TEST_OBJ) tests/texture.o -o $@ $(LDFLAGS)

test_material: tests/material.o $(OBJ) $(LDLIBS) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) $(TEST_OBJ) tests/material.o -o $@ $(LDFLAGS)

test_parser: tests/parser.o $(OBJ) $(LDLIBS) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) $(TEST_OBJ) tests/parser.o -o $@ $(LDFLAGS)

-include $(DEP)

clean:
	$(RM) $(OBJ) $(DEP) $(DRIVER_OBJ) $(DRIVER_DEP)
	$(RM) $(TEST_OBJ) $(TEST_DEP) $(TESTER_OBJ) $(TESTER_DEP)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME) $(BONUS)
	$(RM) test_vectors test_camera test_texture test_material test_parser
	@make fclean -C $(LIBFT_DIR)

re:
	@make fclean
	@make all

.PHONY: all bonus clean fclean re
