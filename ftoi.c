#include "rtv1.h"

double   ftoi(char *str)
{
    size_t	i;
	double	n;
	double	sign;
    double   buf;
    
    buf = 1;
    sign = str[0] == '-' ? -1 : 1;
    i = sign == 1 ? 0 : 1;
    while(str[i] != '\0' && str[i] != '.')
    {
        n *= 10;
		n += (str[i] - '0');
		i++;
    }
    str[i] != '\0' ? i += 1 : 0;
    while(str[i] != '\0')
    {
		n += (str[i] - '0') / (10 * buf);
        buf *= 10;
		i++;
    }
    return(n * sign);
}
