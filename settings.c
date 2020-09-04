#include "rtv1.h"

void sphere_settings(t_sphere *s, t_ray *r)
{
    /*s->center.x = WID/2;
    s->center.y = HEI/2;
    s->center.z = 100;
    s->radius = 200;*/
    r->dir.x = 0;
    r->dir.y = 0;
    r->dir.z = 1;
    r->start.z = 0;
}
