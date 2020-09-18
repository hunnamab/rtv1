#include "rtv1.h"

void get_objects(char *scene)
{
    char *obj_name;
    int obj_quantity;
    int i;
    int len;

    i = 0;
    len = ft_strlen(scene);
    while (i < len)
    {
        if (scene[i + 1] == '{')
        {
            obj_name = ft_strsub(scene, 0, i);
            obj_quantity++;
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
