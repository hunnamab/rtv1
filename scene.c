#include "rtv1.h"

void     init_scene(t_scene *scene)
{
    scene->camera.position = get_point(10,10, -10);
    scene->viewport = get_viewport(&scene->camera);
    scene->ray_buf = get_rays_arr(&scene->camera, scene->viewport);
    scene->normal_buf = malloc(sizeof(t_point) * (WID * HEI));
    scene->material_buf = malloc(sizeof(t_material) * (WID * HEI));
    scene->intersection_buf = malloc(sizeof(t_point) * (WID * HEI));
    get_buffers(scene);
}