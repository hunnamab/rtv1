#include "rtv1.h"

int main(int args, char **argv)
{
    int         fd;
    t_sdl       sdl;
    t_object    **buf;
    t_scene     *scene;

    scene = malloc(sizeof(t_scene));
    if (args != 2)
    {
        ft_putstr("usage: ./rtv1 [scene_file]\n");
        return (0);
    }
    else
    {
        fd = open(argv[1], O_RDONLY);
        buf = read_scene(fd, &scene->obj_nmb, &scene->light_nmb); // scene_reader.c
        close(fd);
        printf("obj_nmb = %d\n", scene->obj_nmb);
        printf("light_nmb = %d\n", scene->light_nmb);
        scene->objs = get_objects_structures(scene->obj_nmb, buf); // get_structures.c
        scene->light = get_light_structures(scene->light_nmb, buf); // get_structures.c
        //return (0);
    }
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(WID, HEI, 0, &sdl.win, &sdl.renderer);
    SDL_RenderClear(sdl.renderer);
    init_scene(scene);
    draw_scene(&sdl, scene);
    //draw_normal_buf(&sdl, scene);
    while (1)
    {
       if (SDL_PollEvent(&sdl.event))
        {
            if (SDL_QUIT == sdl.event.type || SDLK_ESCAPE == sdl.event.key.keysym.sym)
                break ;
        }
    }
    SDL_DestroyRenderer(sdl.renderer);
    SDL_DestroyWindow(sdl.win);
    SDL_Quit();
    return (0);
}
