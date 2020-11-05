#include "rtv1.h"

void     init_scene(t_scene *scene)
{
    double **matrix;
    scene->camera.position = get_point(0, 10, -40);
    scene->viewport = get_viewport(&scene->camera);
    scene->ray_buf = get_rays_arr(&scene->camera, scene->viewport);
    scene->normal_buf = malloc(sizeof(t_point) * WID * HEI);
    scene->material_buf = malloc(sizeof(t_material) * WID * HEI);
    scene->intersection_buf = malloc(sizeof(t_point) * WID * HEI);
    scene->index_buf = malloc(sizeof(int) * WID * HEI);
    scene->depth_buf = malloc(sizeof(double) * WID * HEI);
     matrix = get_transform_matrix(get_three_doubles(0,0,0.3),get_three_doubles(0,0,0),get_three_doubles(1,1,1));
    int x = 0;
    while(x < WID * HEI)
    {
        transform(&scene->ray_buf[x].dir, matrix, 1);
        x++;
    }
    get_closest_points(scene);
    get_intersection_buf(scene);
    get_normal_buf(scene);
    get_material_buf(scene);
}