#include "rtv1.h"

t_light     *new_light(t_point position, t_point direction, const char *type)
{
    t_light *new_light;

    new_light = malloc(sizeof(t_light));
    new_light->type = ft_strcpy_alloc(new_light->type, type);
    if (ft_strequ(new_light->type, "point"))
        new_light->intensity = 0.2;
    else
        new_light->intensity = 0.2;
    new_light->position = position;
    new_light->direction = direction;
    return(new_light);
}

t_color     reflection_color(t_scene *scene, int index)
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
    while (j < scene->light_nmb)
    {
        if (ft_strequ(scene->light[j]->type, "ambient"))
            i += scene->light[j]->intensity;
        else
        {
            if (ft_strequ(scene->light[j]->type, "point"))
                L = vector_sub(&scene->light[j]->position, &scene->intersection_buf[index]);
            if (ft_strequ(scene->light[j]->type, "directional"))
                L = scene->light[j]->direction;
            n_dot_l = vector_dot(&scene->normal_buf[index], &L);
            if (n_dot_l > 0)
                i += (scene->light[j]->intensity * n_dot_l) / vector_length(&L);
        }
         if (scene->material_buf[index].specular != -1) // коэффициент s должен быть положительным числом, если объект обладает свойством зеркальности
            {
                // для каждого идеально отполированного объекта падающий луч отражается в единственном направлении R (зеркальное отражение)
                // высчитываем это значение по формуле
                R = vector_scale(2.0, &scene->normal_buf[index]);
                R = vector_scale(n_dot_l, &R);
                R = vector_sub(&R, &L);
                // D это -V, где V это вектор, направленный из камеры к объекту (т.е. по сути это направление луча)
                // D это «вектор обзора», указывающий из точки (P) в камеру
                // т.е. для не идеально отполированных поверхностей свет отражается не только в направлении R,
                // но и в приближенных к нему направлениях, что мы и задаем как "вектор обзора" D
                D.x = -scene->ray_buf[index].dir.x;
                D.y = -scene->ray_buf[index].dir.y;
                D.z = -scene->ray_buf[index].dir.z;
                // скалярное произведение зеркального отражения и вектора, указывающего от объекта в камеру
                r_dot_v = vector_dot(&R, &D);
                if (r_dot_v > 0)
                    i += scene->light[j]->intensity * pow((double)r_dot_v / (vector_length(&R) * vector_length(&D)), scene->material_buf[index].specular);
            }
        j++;
    }
    i = i > 1 ? 1 : i;
    result_color.red = (scene->material_buf[index].color.red * i > 255) ? 255 : (scene->material_buf[index].color.red * i);
    result_color.green = (scene->material_buf[index].color.green * i > 255) ? 255 : (scene->material_buf[index].color.green * i);
    result_color.blue = (scene->material_buf[index].color.blue * i > 255) ? 255 : (scene->material_buf[index].color.blue * i);
    return (result_color);
}
