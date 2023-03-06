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

FILENAME		= \
				threadman_bonus \
				timeman_bonus \
				geometry/matrix_init_bonus \
				geometry/matrix_inverse_bonus \
				geometry/matrix_inverse_utils_bonus \
				geometry/multiply_bonus \
				geometry/rotate_bonus \
				geometry/translate_bonus \
				geometry/vec_setval_bonus \
				geometry/vec3_add_bonus \
				geometry/vec3_cross_bonus \
				geometry/vec3_dot_bonus \
				geometry/vec3_mult_bonus \
				geometry/vec3_sub_bonus \
				geometry/vec3_reflect_refract_bonus \
				geometry/vec3_utils1_bonus \
				geometry/vec3_utils2_bonus \
				geometry/vec3_utils3_bonus \
				ray/utils_bonus \
				number/random_bonus \
				number/random_multithread_bonus \
				number/degree_bonus \
				number/utils_bonus \
				ptrarr/create_bonus \
				ptrarr/getter_bonus \
				print/print0_bonus \
				print/print1_bonus \
				print/print2_bonus \
				mlx_interface/create_bonus \
				mlx_interface/key_interface_bonus \
				mlx_interface/putpixel_bonus \
				mlx_interface/saveimg_bonus \
				mlx_interface/imgwrapper_create_bonus \
				mlx_interface/imgwrapper_methods_bonus \
				mlx_interface/imgwrapper_transform_bonus \
				mlx_interface/mlxman_bonus \
				camera/init_bonus \
				camera/get_ray_at_bonus \
				bounding_box/init_bonus \
				hittable/methods_bonus \
				hittable/math_utils_bonus \
				hittable/hit_record_set_normal_and_face_bonus \
				hittable/sphere_bonus \
				hittable/plane_bonus \
				hittable/disk_bonus \
				hittable/tube_bonus \
				hittable/cylinder_bonus \
				hittable/list_bonus \
				hittable/transform_bonus \
				hittable/cone_bonus \
				hittable/conical_hat_bonus \
				hittable/aa_rectangle_create_bonus \
				hittable/aa_rectangle_hit_bonus \
				hittable/aa_box_bonus \
				hittable/tube_set_uv_bonus \
				material/diffuse_light_bonus \
				material/metal_bonus \
				material/dielectric_bonus \
				material/lambertian_bonus \
				material/methods_bonus \
				texture/destroy_bonus \
				texture/solid_bonus \
				texture/checker_bonus \
				texture/image_bonus \
				parser/parse_scene_bonus \
				parser/parse_settings_bonus \
				parser/settingman_bonus \
				parser/managers1_bonus \
				parser/managers2_bonus \
				parser/managers3_bonus \
				parser/tokenizer_bonus \
				parser/get_tokentype_bonus \
				parser/parse_lines_bonus \
				parser/parse_lines_utils_bonus \
				parser/parse_line_bonus \
				parser/builder/add_resource_bonus \
				parser/builder/utils_bonus \
				parser/builder/checkrange_bonus \
				parser/builder/build_setting_display_bonus \
				parser/builder/build_setting_camera_bonus \
				parser/builder/build_setting_renderer_bonus \
				parser/builder/build_ambient_lighting_bonus \
				parser/builder/build_camera_bonus \
				parser/builder/build_light_bonus \
				parser/builder/build_sphere_bonus \
				parser/builder/build_sphere_patternmatcher_bonus \
				parser/builder/build_plane_bonus \
				parser/builder/build_plane_patternmatcher_bonus \
				parser/builder/build_cylinder_bonus \
				parser/builder/build_cylinder_patternmatcher_bonus \
				parser/builder/build_cone_bonus \
				parser/builder/build_cone_patternmatcher_bonus \
				parser/builder/build_box_bonus \
				parser/builder/build_box_with_color_bonus \
				parser/builder/build_box_with_material_bonus \
				parser/builder/build_box_patternmatcher_bonus \
				parser/builder/build_texture_solid_bonus \
				parser/builder/build_texture_checker_bonus \
				parser/builder/build_texture_image_bonus \
				parser/builder/build_material_lambertian_bonus \
				parser/builder/build_material_metal_bonus \
				parser/builder/build_material_dielectric_bonus \
				parser/builder/build_material_diffuse_light_bonus \
				scene/create_bonus \
				scene/destroy_bonus \
				scene/search_bonus \
				renderer/init_bonus \
				renderer/render_bonus \
				renderer/render_multithread_bonus \
				renderer/render_multithread_workers_bonus \
				renderer/utils_bonus \
				renderer/render_pixel_bonus \
				renderer/render_loop_bonus \
				renderer/write_color_bonus \
				renderer/worker_getter_bonus \
				renderer/worker_setter_bonus \

SRC				= $(addprefix $(DIR_SRC), $(addsuffix .c, $(FILENAME)))
OBJ				= $(addprefix $(DIR_OBJ), $(addsuffix .o, $(FILENAME)))
DEP				= $(addprefix $(DIR_OBJ), $(addsuffix .d, $(FILENAME)))

DRIVER_FILENAME	= main_bonus
DRIVER_SRC		= $(addprefix $(DIR_SRC), $(addsuffix .c, $(DRIVER_FILENAME)))
DRIVER_OBJ		= $(addprefix $(DIR_OBJ), $(addsuffix .o, $(DRIVER_FILENAME)))
DRIVER_DEP		= $(addprefix $(DIR_OBJ), $(addsuffix .d, $(DRIVER_FILENAME)))

################################# TARGETS ######################################
all: $(NAME)

$(DIR_OBJ)%.o: $(DIR_SRC)%.c
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
	$(RM) $(DIR_OBJ)
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
