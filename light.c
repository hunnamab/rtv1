#include "rtv1.h"

t_color     reflection_color(t_point *P, t_point *N, t_color *s_color)
{
    float i;
    t_light light;
    t_point L;
    float n_dot_l;
    t_color result_color;

    i = 0;
    //тут пока только заполняющий источник света
    light.intensity = 0.2;
    i += light.intensity;
    light.position = get_point(WID/2, HEI, -100);
    light.direction = get_point(2, 1, 0);
    //берем вектор из точки пересечения P к позиции источника света
    L = vector_sub(&light.position, P);
    //скалярное произвеление нормали и позиции света
    n_dot_l = vector_dot(N, &L);
    //складываем все это дело для получаение коэффициента i
    //i может быть больше единицы
    if (n_dot_l > 0)
        i += light.intensity * n_dot_l / vector_length(&L);
    result_color.red = s_color->red * i;
    result_color.green = s_color->green * i;
    result_color.blue = s_color->blue * i;
    return(result_color);
}
