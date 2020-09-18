#include "rtv1.h"

t_object *get_parameters(char *name, char *description)
{
    t_object *obj;

    if (!ft_strcmp(name, "sphere"))
    {
        printf("sphere");
        obj = get_sphere(description);
    }
    else if (!ft_strcmp(name, "triangle"))
    {
        printf("triangle");
        obj = get_triangle(description);
    }
    /* else if (!ft_strcmp(name, "cone"))
    {
        printf("cone");
    }
    else if (!ft_strcmp(name, "cylinder"))
    {
        printf("cylinder");
    }
    else if (!ft_strcmp(name, "plane"))
    {
        printf("plane");
    }
    else if (!ft_strcmp(name, "light"))
    {
        printf("light");
    }
    else if (!ft_strcmp(name, "camera"))
    {
        printf("camera");
    } */
    else
        return (NULL);
    return (obj);
}

char *get_description(char *scene, int i)
{
    char *description;
    int len;
    int start;

    len = 0;
    start = i;
    while (scene[i + 1] != '}')
    {
        i++;
        len++;
    }
    description = ft_strsub(scene, start, len);
    return (description);
}

void get_objects(char *scene)
{
    t_object **objs;
    char *obj_name;
    char *obj_desc;
    int obj_num;
    int start;
    int n;
    int i;
    int len;

    i = 0;
    len = ft_strlen(scene);
    obj_num = 0;
    // выясняем кол-во объектов сцены
    while (i < len)
    {
        if (scene[i] == '{')
            obj_num++;
        i++;
    }
    // создаем массив структур для объектов
    objs = malloc(sizeof(t_object *) * obj_num);
    i = 0;
    n = 0;
    start = 0;
    while (i < len)
    {
        if (scene[i + 1] == '{' && n < obj_num)
        {
            // записываем название объекта
            obj_name = ft_strsub(scene, start, (i - start));
            // записываем описание объекта
            obj_desc = get_description(scene, i + 3);
            // создаем объект и получаем его характеристики
            objs[n] = get_parameters(obj_name, obj_desc);
            // освобождаем строки
            free(obj_name);
            free(obj_desc);
            // плюсуем индекс массива
            n++;
            // переходим к описанию следующего объекта
            while (scene[i] != '}')
                i++;
            start = i + 3;
        }
        i++;
    }
}

void read_scene(int fd)
{
    int		ret;
	char	buf[64000];

	while ((ret = read(fd, buf, 64000)) > 0)
		buf[ret] = '\0';
	get_objects(buf);
}
