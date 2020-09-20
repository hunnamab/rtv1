#include "rtv1.h"

t_point     get_point(float x, float y, float z)
{
    t_point result;

    result.x = x;
    result.y = y;
    result.z = z;
    return (result);
}

t_color     get_color(int r, int g, int b, int a)
{
    t_color result;

    result.red = r;
    result.green = g;
    result.blue = b;
    result.alpha = a;
    return(result);
}