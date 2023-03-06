#ifndef PRINT_H
# define PRINT_H

# include "geometry.h"
# include "camera.h"
# include "ray.h"
# include "hittable.h"

void	print_vec2(const t_vec2 *vec2);
void	print_vec3(const t_vec3 *vec3);
void	print_ray(const t_ray *ray);
void	print_mtx44(const t_mtx44 *mtx44);
void	print_camera(const t_camera *cam);
void	print_hit_record(const t_hit_record *rec);
void	print_scatter_record(const t_scatter_record *rec);
void	print_cylinder_info(const t_cylinder_info *info);
void	print_cone_info(const t_cone_info *info);
void	print_bbox(const t_bbox *bbox);
void	print_box(const t_hittable *box);

#endif
