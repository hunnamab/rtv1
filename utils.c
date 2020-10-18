#include "rtv1.h"

t_point     get_point(float x, float y, float z)
{
    t_point result;

    result.x = x;
    result.y = y;
    result.z = z;
    return (result);
}

t_point     *get_viewport_coords(t_camera *camera)
{
    int x;
    int y;
    t_point *viewport;
    int i;

    i = 0;
    viewport = malloc(sizeof(t_point) * (WID * HEI));
    x = 0;
    y = 0;
    while(y < HEI)
    {
        while(x < WID)
        {
            view_port_point[i].y = -(y - (float)HEI / 2) * (1 / (float)HEI) + camera->pos.y;
            view_port_point[i].x = (x - (float)WID / 2) * (((float)WID / (float)HEI)/ (float)WID) +  camera->pos.x;
            view_port_point[i].z = camera->pos.z + 1;
            i++;
            x++;
        }
        x = 0;
        y++;
    }
    return(viewport);
}