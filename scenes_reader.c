#include "rtv1.h"

void read_scene(int fd)
{
    int		ret;
	char	buf[64000];
	int		i;

	i = 0;
	while ((ret = read(fd, buf, 64000)) > 0)
		buf[ret] = '\0';
	ft_putstr(buf);
}
