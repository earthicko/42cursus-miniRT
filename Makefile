NAME			= miniRT
################################# LIBRARIES ####################################
LIBFT_DIR		= libft
LIBFT			= $(LIBFT_DIR)/libft.a
LINK_LIBFT		= -L$(LIBFT_DIR)
INC_DIR_LIBFT	= -I$(LIBFT_DIR)/includes

LINK_LIBM		= -lm
LINK_PTHREAD	= -pthread

LDLIBS			= $(LIBFT) $(LIBMLX)
LDFLAGS			= $(LINK_LIBFT) $(LINK_LIBMLX) $(LINK_LIBM) $(LINK_PTHREAD)

INC_DIR			= -I. -Iincludes $(INC_DIR_LIBFT)
################################# COMMANDS #####################################
RM				= rm -rf
CFLAGS			= -Wall -Werror -Wextra -MMD -MP $(ACFLAGS) $(INC_DIR)
################################ FILENAMES #####################################
DIR_SRC			= srcs/
DIR_OBJ			= objs/
DIR_TEST_SRC	= tests/
DIR_TEST_OBJ	= test_objs/

FILENAME		= \
				timeman \
				threadman \
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
				geometry/vec3_utils3 \
				ray/utils \
				number/random \
				number/random_multithread \
				number/degree \
				number/utils \
				ptrarr/create \
				ptrarr/getter \
				print/print0 \
				print/print1 \
				print/print2 \
				display/create \
				display/putpixel \
				display/saveimg \
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
				hittable/cone \
				hittable/conical_hat \
				hittable/aa_rectangle_create \
				hittable/aa_rectangle_hit \
				hittable/aa_box \
				hittable/tube_set_uv \
				material/diffuse_light \
				material/metal \
				material/dielectric \
				material/lambertian \
				material/methods \
				texture/destroy \
				texture/solid \
				texture/checker \
				texture/image \
				parser/parse_scene \
				parser/parse_settings \
				parser/settingman \
				parser/managers1 \
				parser/managers2 \
				parser/managers3 \
				parser/tokenizer \
				parser/get_tokentype \
				parser/parse_lines \
				parser/parse_lines_utils \
				parser/parse_line \
				parser/builder/add_resource \
				parser/builder/utils \
				parser/builder/checkrange \
				parser/builder/build_setting_display \
				parser/builder/build_setting_camera \
				parser/builder/build_setting_renderer \
				parser/builder/build_ambient_lighting \
				parser/builder/build_camera \
				parser/builder/build_light \
				parser/builder/build_sphere \
				parser/builder/build_sphere_patternmatcher \
				parser/builder/build_plane \
				parser/builder/build_plane_patternmatcher \
				parser/builder/build_cylinder \
				parser/builder/build_cylinder_patternmatcher \
				parser/builder/build_cone \
				parser/builder/build_cone_patternmatcher \
				parser/builder/build_box \
				parser/builder/build_box_with_color \
				parser/builder/build_box_with_material \
				parser/builder/build_box_patternmatcher \
				parser/builder/build_texture_solid \
				parser/builder/build_texture_checker \
				parser/builder/build_texture_image \
				parser/builder/build_material_lambertian \
				parser/builder/build_material_metal \
				parser/builder/build_material_dielectric \
				parser/builder/build_material_diffuse_light \
				scene/create \
				scene/destroy \
				scene/search \
				renderer/init \
				renderer/render \
				renderer/render_multithread \
				renderer/render_multithread_workers \
				renderer/utils \
				renderer/render_pixel \
				renderer/render_loop \
				renderer/write_color \
				renderer/worker_getter \
				renderer/worker_setter \
				xpmwrapper/init \
				xpmwrapper/utils \
				xpmwrapper/load \
				xpmwrapper/parse \
				xpmwrapper/getcolor \
				xpmwrapper/transform \

SRC				= $(addprefix $(DIR_SRC), $(addsuffix .c, $(FILENAME)))
OBJ				= $(addprefix $(DIR_OBJ), $(addsuffix .o, $(FILENAME)))
DEP				= $(addprefix $(DIR_OBJ), $(addsuffix .d, $(FILENAME)))

DRIVER_FILENAME	= main
DRIVER_SRC		= $(addprefix $(DIR_SRC), $(addsuffix .c, $(DRIVER_FILENAME)))
DRIVER_OBJ		= $(addprefix $(DIR_OBJ), $(addsuffix .o, $(DRIVER_FILENAME)))
DRIVER_DEP		= $(addprefix $(DIR_OBJ), $(addsuffix .d, $(DRIVER_FILENAME)))

TEST_FILENAME	= \
				vectors_arithmetic \

TEST_SRC		= $(addprefix $(DIR_TEST_SRC), $(addsuffix .c, $(TEST_FILENAME)))
TEST_OBJ		= $(addprefix $(DIR_TEST_OBJ), $(addsuffix .o, $(TEST_FILENAME)))
TEST_DEP		= $(addprefix $(DIR_TEST_OBJ), $(addsuffix .d, $(TEST_FILENAME)))

TESTER_FILENAME	= \
				vectors \
				camera \
				hittable \
				texture \
				material \
				parser \
				mtx_inverse \
				tube \
				transform \
				cone_create \

TESTER_SRC		= $(addprefix $(DIR_TEST_SRC), $(addsuffix .c, $(TESTER_FILENAME)))
TESTER_OBJ		= $(addprefix $(DIR_TEST_OBJ), $(addsuffix .o, $(TESTER_FILENAME)))
TESTER_DEP		= $(addprefix $(DIR_TEST_OBJ), $(addsuffix .d, $(TESTER_FILENAME)))

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

test_vectors: test_objs/vectors.o $(OBJ) $(LDLIBS) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) $(TEST_OBJ) test_objs/vectors.o -o $@ $(LDFLAGS)

test_camera: test_objs/camera.o $(OBJ) $(LDLIBS) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) $(TEST_OBJ) test_objs/camera.o -o $@ $(LDFLAGS)

test_hittable: test_objs/hittable.o $(OBJ) $(LDLIBS) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) $(TEST_OBJ) test_objs/hittable.o -o $@ $(LDFLAGS)

test_texture: test_objs/texture.o $(OBJ) $(LDLIBS) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) $(TEST_OBJ) test_objs/texture.o -o $@ $(LDFLAGS)

test_material: test_objs/material.o $(OBJ) $(LDLIBS) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) $(TEST_OBJ) test_objs/material.o -o $@ $(LDFLAGS)

test_parser: test_objs/parser.o $(OBJ) $(LDLIBS) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) $(TEST_OBJ) test_objs/parser.o -o $@ $(LDFLAGS)
	
test_tube: test_objs/tube.o $(OBJ) $(LDLIBS) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) $(TEST_OBJ) test_objs/tube.o -o $@ $(LDFLAGS)

test_pointer_speed: test_objs/pointer_speed_compare.o $(OBJ) $(LDLIBS) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) $(TEST_OBJ) test_objs/pointer_speed_compare.o -o $@ $(LDFLAGS)

test_mtx_inverse: test_objs/mtx_inverse.o $(OBJ) $(LDLIBS) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) $(TEST_OBJ) test_objs/mtx_inverse.o -o $@ $(LDFLAGS)

test_transform: test_objs/transform.o $(OBJ) $(LDLIBS) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) $(TEST_OBJ) test_objs/transform.o -o $@ $(LDFLAGS)

test_cone_create: test_objs/cone_create.o $(OBJ) $(LDLIBS) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) $(TEST_OBJ) test_objs/cone_create.o -o $@ $(LDFLAGS)

test_aa_rect_create: test_objs/aa_rect_create.o $(OBJ) $(LDLIBS) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) $(TEST_OBJ) test_objs/aa_rect_create.o -o $@ $(LDFLAGS)

test_cone_ray_intersect: test_objs/cone_ray_intersect.o $(OBJ) $(LDLIBS) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) $(TEST_OBJ) test_objs/cone_ray_intersect.o -o $@ $(LDFLAGS)

test_xpmwrapper: test_objs/xpmwrapper.o $(OBJ) $(LDLIBS) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) $(TEST_OBJ) test_objs/xpmwrapper.o -o $@ $(LDFLAGS)

-include $(DEP)

clean:
	$(RM) $(DIR_OBJ) $(DIR_TEST_OBJ)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME) $(BONUS)
	$(RM) \
		test_vectors test_camera test_texture test_material test_parser \
		test_hittable test_pointer_speed test_mtx_inverse test_transform \
		test_cone_create test_aa_rect_create test_xpmwrapper
	@make fclean -C $(LIBFT_DIR)

re:
	@make fclean
	@make all

.PHONY: all bonus clean fclean re
