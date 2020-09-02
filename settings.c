#include "rtv1.h"

void sphere_settings(t_sphere *s, t_ray *r)
{
    s->center.x = 200;
    s->center.y = 200;
    s->center.z = 100;
    s->radius = 100;
    r->dir.x = 0;
    r->dir.y = 0;
    r->dir.z = 1;
    r->start.z = 0;
}
