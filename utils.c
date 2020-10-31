#include "rtv1.h"

t_point     get_point(float x, float y, float z)
{
    t_point result;

    result.x = x;
    result.y = y;
    result.z = z;
    return (result);
}

void        copy_point(t_point *dst, t_point *src)
{
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
}

t_point     *get_viewport(t_camera *camera)
{
    int x;
    int y;
    t_point *viewport;
    float k;

    k = (float)WID / (float)HEI;
    viewport = malloc(sizeof(t_point) * (WID * HEI));
    x = 0;
    y = 0;
    while(y < HEI)
    {
        while(x < WID)
        {
            viewport[y * WID + x].y = -(y - (float)HEI / 2) * (1 / (float)HEI) + camera->position.y;
            viewport[y * WID + x].x = (x - (float)WID / 2) * (k / (float)WID) + camera->position.x;
            viewport[y * WID + x].z = camera->position.z + 1;
            x++;
        }
        x = 0;
        y++;
    }
    return(viewport);
}