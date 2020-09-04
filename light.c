#include "rtv1.h"

void     reflection_color(t_point *P, t_point *N, t_color *color)
{
    float i;
    t_light light;
    t_point L;
    float n_dot_l;

    i = 0.5;
    /*light.intencity = 0.6;
    light.position = get_point(2, 1, 0);
    light.direction = get_point(2, 1, 0);
    L = vector_sub(&light.position, P);
    n_dot_l = vector_dot(N, &light.position);
    if (n_dot_l > 0)
        i += light.intencity * n_dot_l / (vector_length(&L));
    //printf("i == %f\n", i);*/
    color->red = color->red * i;
    //color->green = 255 * i;
    //color->blue = 255 * i;
}