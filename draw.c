#include "rtv1.h"

void draw_sphere(t_sdl *sdl)
{
    t_ray r;
    t_object **s; //теперь создаем объект сферический
    int x;
    int y;
    int is_intersect;
    int obj_num;
    int j = 200;
    int i = 0;
    float t0;
    float t1;
    t_color color;

    obj_num = 4;
    s = malloc(sizeof(t_object *) * obj_num);
    for (int f = 0; f < 3; f++)
    {
        s[f] = new_sphere(get_point(j, (HEI/2 + j/5), j / 2), 90); // new_objects.c
        j+= 200;
    }
    color.alpha = 255;
    s[1]->color.red = 0;
    s[1]->color.blue = 255;
    s[2]->color.red = 0;
    s[2]->color.green = 255;
    s[3] = new_triangle(get_point(300, 300, 0), get_point(200, 200, 0), get_point(400, 200, 0)); // new_objects.c
    //s[3] = new_sphere(get_point(100, 100, 100), 90);
    sphere_settings((t_sphere *)s[0]->data, &r); //settings.c
    x = 0;
    y = 0;
    is_intersect = 0;
    while (y < HEI)
    {
        r.start.y = y;
        r.start.z = 0;
        while (x < WID)
        {
            r.start.x = x;
            while(i < obj_num)
            {
                is_intersect = s[i]->intersect(&r, s[i], &color); //sphere.c
                if (is_intersect)
                {
                    SDL_SetRenderDrawColor(sdl->renderer, color.red, color.green, color.blue, color.alpha);
                    SDL_RenderDrawPoint(sdl->renderer, x, y);
                    break;
                }
                else
                {
                    SDL_SetRenderDrawColor(sdl->renderer, 0, 0, 0, 255);
                    SDL_RenderDrawPoint(sdl->renderer, x, y);
                }
                i++;
            }
            x++;
            is_intersect = 0;
            i = 0;
        }
        x = 0;
        y++;
    }
    SDL_RenderPresent(sdl->renderer);
}
