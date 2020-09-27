#include "rtv1.h"

t_light     *new_light(t_point position, t_point direction, const char *type)
{
    t_light *new_light;

    new_light = malloc(sizeof(t_light));
    new_light->type = ft_strcpy_alloc(new_light->type, type);
    if(ft_strequ(new_light->type, "point"))
        new_light->intensity = 0.6;
    else
        new_light->intensity = 0.2;
    new_light->position = position;
    new_light->direction = direction;
    return(new_light);
}

t_color     reflection_color(t_point *P, t_point *N, t_point *V, t_object *o, t_light **light)
{
    float i;
    t_color result_color;
    t_point L;
    t_point R;
    t_point D;
    float n_dot_l;
    float r_dot_v;
    int j;

    j = 0;
    i = 0;
    while(light[j])
    {
        if (ft_strequ(light[j]->type, "point"))
        {
            L = vector_sub(&light[j]->position, P);
            n_dot_l = vector_dot(N, &L);
            if (n_dot_l > 0)
                i += (light[j]->intensity * n_dot_l) / vector_length(&L);
        }
        if (ft_strequ(light[j]->type, "ambient"))
            i += light[j]->intensity;
        if (ft_strequ(light[j]->type, "directional"))
        {
            L = light[j]->direction;
            n_dot_l = vector_dot(N, &L);
            if (n_dot_l > 0)
                i += (light[j]->intensity * n_dot_l) / vector_length(&L);
        }
        if (o->specular != -1) // коэффициент s должен быть положительным числом, если объект обладает свойством зеркальности
            {
                // для каждого идеально отполированного объекта падающий луч отражается в единственном направлении R (зеркальное отражение)
                // высчитываем это значение по формуле
                R = vector_scale(2.0, N);
                R = vector_scale(n_dot_l, &R);
                R = vector_sub(&R, &L);
                // D это -V, где V это вектор, направленный из камеры к объекту (т.е. по сути это направление луча)
                // D это «вектор обзора», указывающий из точки (P) в камеру
                // т.е. для не идеально отполированных поверхностей свет отражается не только в направлении R,
                // но и в приближенных к нему направлениях, что мы и задаем как "вектор обзора" D
                D.x = -V->x;
                D.y = -V->y;
                D.z = -V->z;
                // скалярное произведение зеркального отражения и вектора, указывающего от объекта в камеру
                r_dot_v = vector_dot(&R, &D);
                if (r_dot_v > 0)
                    i += light[j]->intensity * pow((double)r_dot_v / (vector_length(&R) * vector_length(&D)), o->specular);
            }
        j++;
    }
    i = i > 1 ? 1 : i;
    result_color.red = o->color.red * i > 255 ? 255 : o->color.red * i;
    result_color.green = o->color.green * i > 255 ? 255 : o->color.green * i;
    result_color.blue = o->color.blue * i > 255 ? 255 : o->color.blue * i;
    return (result_color);
}
