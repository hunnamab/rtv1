#include "rtv1.h"

t_object *get_parameters(char *name, char **description)
{
    t_object *obj;

    if (!ft_strcmp(name, "sphere"))
    {
        printf("sphere\n");
        obj = get_sphere(description); // objects_parameters.c
    }
    else if (!ft_strcmp(name, "triangle"))
    {
        printf("triangle\n");
        obj = get_triangle(description);
    }
    else if (!ft_strcmp(name, "plane"))
    {
        printf("plane\n");
        obj = get_plane(description);
    }
    /* else if (!ft_strcmp(name, "cone"))
    {
        printf("cone\n");
    }
    else if (!ft_strcmp(name, "cylinder"))
    {
        printf("cylinder\n");
    }
    else if (!ft_strcmp(name, "light"))
    {
        printf("light\n");
    }
    else if (!ft_strcmp(name, "camera"))
    {
        printf("camera\n");
    } */
    else
        return (NULL);
    return (obj);
}

char **get_description(char *scene, int i)
{
    char *descr_buf;
    char **description;
    int len;
    int start;

    len = 0;
    start = i;
    while (scene[i + 1] != '}')
    {
        i++;
        len++;
    }
    descr_buf = ft_strsub(scene, start, len);
    description = ft_strsplit(descr_buf, '\n');
    return (description);
}

t_object **get_objects(char *scene, int *obj_nmb)
{
    t_object **objs;
    char *obj_name;
    char **obj_desc;
    int nmb;
    int start;
    int n;
    int i;
    int len;

    i = 0;
    len = ft_strlen(scene);
    nmb = 0;
    // выясняем кол-во объектов сцены
    while (i < len)
    {
        if (scene[i] == '{')
            nmb++;
        i++;
    }
    *(int *)obj_nmb = nmb;
    // создаем массив структур для объектов
    objs = malloc(sizeof(t_object *) * nmb);
    i = 0;
    n = 0;
    start = 0;
    while (i < len)
    {
        if (scene[i + 1] == '{' && n < nmb)
        {
            // записываем название объекта
            obj_name = ft_strsub(scene, start, (i - start));
            // записываем описание объекта
            obj_desc = get_description(scene, i + 3);
            // создаем объект и получаем его характеристики
            objs[n] = get_parameters(obj_name, obj_desc);
            // освобождаем строки
            free(obj_name);
            //free(obj_desc);
            // плюсуем индекс массива
            n++;
            // переходим к описанию следующего объекта
            while (scene[i] != '}')
                i++;
            start = i + 3;
        }
        i++;
    }
    return (objs);
}

t_object **read_scene(int fd, int *obj_nmb)
{
    int		ret;
	char	buf[64000];

	while ((ret = read(fd, buf, 64000)) > 0)
		buf[ret] = '\0';
	return (get_objects(buf, obj_nmb));
}
