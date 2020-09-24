#include "rtv1.h"

t_color     reflection_color(t_point *P, t_point *N, t_point *V, t_object *o)
{
    float i;
    t_color result_color;
    t_light light;
    t_point L;
    t_point R;
    t_point D;
    float n_dot_l;
    float r_dot_v;

    i = 0;
    //тут пока только заполняющий источник света
    light.intensity = 0.2;
    i += light.intensity;
    light.position = get_point(WID * 2, HEI/3, -10);
    light.direction = get_point(2, 1, 0);
    //берем вектор из точки пересечения P к позиции источника света
    L = vector_sub(&light.position, P);
    //скалярное произведение нормали и позиции света
    n_dot_l = vector_dot(N, &L);
    //складываем все это дело для получение коэффициента i
    //i может быть больше единицы
    if (n_dot_l > 0)
        i += light.intensity * n_dot_l / (vector_length(N) * vector_length(&L));
    // создаем эффект зеркальности
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
            i += light.intensity * pow((double)r_dot_v / (vector_length(&R) * vector_length(&D)), o->specular);
    }
    // получаем цвета
    result_color.red = o->color.red * i;
    result_color.green = o->color.green * i;
    result_color.blue = o->color.blue * i;
    return (result_color);
}
