#include "rtv1.h"

t_color     reflection_color(t_point *P, t_point *N, t_color *s_color)
{
    float i;
    t_light light;
    t_point L;
    float n_dot_l;
    t_color result_color;

    i = 0;
    //эта часть не работает, потому что хз, но цвет меняется нормально
    light.intencity = 0.2;
    i += light.intencity;
    light.position = get_point(WID/2 + 100, HEI/2, 20);
    light.direction = get_point(2, 1, 0);
    L = vector_sub(&light.position, P);
    n_dot_l = vector_dot(N, &light.position);
    if (n_dot_l > 0)
        i += light.intencity * n_dot_l / (vector_length(&L));
    result_color.red = s_color->red * i;
    result_color.green = s_color->green * i;
    result_color.blue = s_color->blue * i;
    return(result_color);
}