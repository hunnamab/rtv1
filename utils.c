#include "rtv1.h"

t_point     get_point(float x, float y, float z)
{
    t_point result;

    result.x = x;
    result.y = y;
    result.z = z;
    return (result);
}
t_color     set_color_zero(t_color *color)
{
    color->red = 0;
    color->green = 0;
    color->blue = 0;
    color->alpha = 0;
}

t_color     set_color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    t_color color;

    color.red = red;
    color.blue = blue;
    color.green = green;
    color.alpha = alpha;
    return(color);
}
void        copy_point(t_point *dst, t_point *src)
{
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
}

void        copy_color(t_color *dst, t_color *src)
{
    dst->red = src->red;
    dst->blue = src->blue;
    dst->green = src->green;
    dst->alpha = src->alpha;
}

t_point     *get_viewport(t_camera *camera)
{
    int x;
    int y;
    t_point *viewport;

    viewport = malloc(sizeof(t_point) * (WID * HEI));
    x = 0;
    y = 0;
    while(y < HEI)
    {
        while(x < WID)
        {
            viewport[y * WID + x].y = -(y - (float)HEI / 2) * (1 / (float)HEI) + camera->position.y;
            viewport[y * WID + x].x = (x - (float)WID / 2) * (((float)WID / (float)HEI)/ (float)WID) +  camera->position.x;
            viewport[y * WID + x].z = camera->position.z + 1;
            x++;
        }
        x = 0;
        y++;
    }
    return(viewport);
}