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
				tube \

TESTER_SRC		= $(addprefix tests/, $(addsuffix .c, $(TESTER_FILENAME)))
TESTER_OBJ		= $(addprefix tests/, $(addsuffix .o, $(TESTER_FILENAME)))
TESTER_DEP		= $(addprefix tests/, $(addsuffix .d, $(TESTER_FILENAME)))

FILENAME		= \
				timeman \
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
				ray/utils \
				number/random \
				number/degree \
				number/utils \
				ptrarr/create \
				ptrarr/getter \
				print/print0 \
				print/print1 \
				mlx_interface/create \
				mlx_interface/key_interface \
				mlx_interface/putpixel \
				mlx_interface/saveimg \
				camera/init \
				camera/get_ray_at \
				bounding_box/init \
				hittable/methods \
				hittable/math_utils \
				hittable/hit_record_set_normal_and_face \
				hittable/sphere \
				hittable/plane \
				hittable/disk \
				hittable/tube \
				hittable/cylinder \
				hittable/list \
				hittable/transform \
				material/diffuse_light \
				material/metal \
				material/dielectric \
				material/lambertian \
				material/methods \
				texture/solid \
				texture/checker \
				parser/parse_scene \
				parser/managers1 \
				parser/managers2 \
				parser/tokenizer \
				parser/get_tokentype \
				parser/parse_lines \
				parser/parse_line \
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
				renderer/render \
				renderer/init \
				renderer/render_pixel \
				renderer/write_color \

SRC				= $(addprefix srcs/, $(addsuffix .c, $(FILENAME)))
OBJ				= $(addprefix srcs/, $(addsuffix .o, $(FILENAME)))
DEP				= $(addprefix srcs/, $(addsuffix .d, $(FILENAME)))
################################# TARGETS ######################################
all: $(NAME)

$(NAME): $(OBJ) $(LDLIBS) $(DRIVER_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) $(DRIVER_OBJ) -o $@ $(LDFLAGS)

$(LIBFT):
	@make -j4 -C $(LIBFT_DIR)/

$(LIBMLX_ORIG):
	@make -C $(LIBMLX_DIR)/

$(LIBMLX): $(LIBMLX_ORIG)
	cp $(LIBMLX_ORIG) .

test_vectors: tests/vectors.o $(OBJ) $(LDLIBS) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) $(TEST_OBJ) tests/vectors.o -o $@ $(LDFLAGS)

test_camera: tests/camera.o $(OBJ) $(LDLIBS) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) $(TEST_OBJ) tests/camera.o -o $@ $(LDFLAGS)

test_hittable: tests/hittable.o $(OBJ) $(LDLIBS) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) $(TEST_OBJ) tests/hittable.o -o $@ $(LDFLAGS)

test_texture: tests/texture.o $(OBJ) $(LDLIBS) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) $(TEST_OBJ) tests/texture.o -o $@ $(LDFLAGS)

test_material: tests/material.o $(OBJ) $(LDLIBS) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) $(TEST_OBJ) tests/material.o -o $@ $(LDFLAGS)

test_parser: tests/parser.o $(OBJ) $(LDLIBS) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) $(TEST_OBJ) tests/parser.o -o $@ $(LDFLAGS)
	
test_tube: tests/tube.o $(OBJ) $(LDLIBS) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) $(TEST_OBJ) tests/tube.o -o $@ $(LDFLAGS)

test_pointer_speed: tests/pointer_speed_compare.o $(OBJ) $(LDLIBS) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) $(TEST_OBJ) tests/pointer_speed_compare.o -o $@ $(LDFLAGS)

-include $(DEP)

clean:
	$(RM) $(OBJ) $(DEP) $(DRIVER_OBJ) $(DRIVER_DEP)
	$(RM) $(TEST_OBJ) $(TEST_DEP) $(TESTER_OBJ) $(TESTER_DEP)
	$(RM) $(LIBMLX)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(LIBMLX_DIR)

fclean: clean
	$(RM) $(NAME) $(BONUS)
	$(RM) test_vectors test_camera test_texture test_material test_parser test_hittable test_pointer_speed
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(LIBMLX_DIR)

re:
	@make fclean
	@make all

.PHONY: all bonus clean fclean re
