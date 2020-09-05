#include "rtv1.h"

t_sphere *new_sphere(t_point center, int16_t radius)
{
    t_sphere *new_sphere;

    new_sphere = malloc(sizeof(t_sphere));
    new_sphere->center = center;
    new_sphere->radius = radius;
    new_sphere->color.red = 255;
    new_sphere->color.green = 0;
    new_sphere->color.blue = 0;
    new_sphere->color.alpha = 255;
    return(new_sphere);
}
t_point     vector_sub_by_scalar(t_point *vector, float scalar)
{
    t_point result;
    result.x = vector->x + scalar;
    result.y = vector->y + scalar;
    result.z = vector->z + scalar;
    return(result);
}
t_point     vector_div_by_scalar(t_point *vector, float scalar)
{
      t_point result;
    result.x = vector->x / scalar;
    result.y = vector->y / scalar;
    result.z = vector->z / scalar;
    return(result);
}

float   vector_length(t_point *vector)
{
    float dot = vector_dot(vector, vector);\
    float result = sqrt(dot);
    return(result);
}

int intersect_ray_sphere(t_ray *r, t_sphere *s, t_color *reflected_color)
{
    float a;
    float b;
    float c;
    float discr;
    float sqrt_discr;
    float t0;
    float t1;
    t_point dist;
    t_point intersection_point;
    t_point normal;

    /*поиск точек пересечения луча и сферы по квадратному уравнению, части которого:
    a - скалярное происзведение направления луча,
    dist - координаты вектора от центра сферы к центру луча
    b - скалярное произведение вектора направления луча и вектора из центра сферы
    c - разница скалярного произведения вектора из центра сферы к началу луча и квадрата радиуса сферы*/
    a = vector_dot(&r->dir, &r->dir);
    dist = vector_sub(&r->start, &s->center);
    b = 2 * vector_dot(&r->dir, &dist);
    c = vector_dot(&dist, &dist) - (s->radius * s->radius);
    /*поиск решений квадратного уравнения
    если решений нет - луч не пересекает сферу, если решение одно - проходит по касательной к сфере
    если два решения - пересекает сферу в двух точках*/
    discr = b * b - 4 * a * c;
    if (discr < 0)
        return (0);
    else
    {
        sqrt_discr = sqrt(discr);
        t0 = (-b + sqrt_discr) / (2 * a);
        t1 = (-b - sqrt_discr) / (2 * a);
        /*t0 и t1 - длина вектора до точек пересечения лучом сферы*/
        t_point buf;
        if (t0 > t1)
        {
            /*выбираем ближайшую точку пересечения со сферой
            умножаем направление луча на т1 или т0
            для получения координат точки пересечения
            прибавляем к координатам начала луча координаты вектора направления*/
            buf = vector_scale(t1, &r->dir);
            intersection_point = vector_add(&r->start, &buf);
        }
        else
        {
            buf = vector_scale(t0, &r->dir);
            intersection_point = vector_add(&r->start, &buf);
        }
        /*для получения значения цвета в точке нужно послать луч, идущий по нормали от
        точки пересечения изначального луча и сферы, в сторону источника света.
        нормаль сферы в конкретной точке - единичный вектор, лежащий на прямой, проходящей
        через центр сферы и искомую точку( в нашем случае через точку пересечения изначального луча и сферы)*/

        normal = vector_sub(&intersection_point, &s->center);
        /*для получения вектора с единичной длиной нужно поделить его на квадратный корень из суммы
        квадратов его компонентов(т.е из его скалярного произведения на самого себя)*/
        normal = vector_div_by_scalar(&normal, vector_length(&normal));
        /*тут рассчитываем сам конечный цвет в файле light.c*/
        *(t_color *)reflected_color = reflection_color(&intersection_point, &normal, &s->color);
        return(1);
    }
    return (0);
}
