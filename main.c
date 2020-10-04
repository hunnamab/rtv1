#include "rtv1.h"

int main(int args, char **argv)
{
    int         fd;
    t_sdl       sdl;
    t_object    **objs;
    t_light     **light;
    int         obj_nmb;

    if (args != 2)
    {
        ft_putstr("usage: ./rtv1 [scene_file]\n");
        return (0);
    }
    else
    {
        fd = open(argv[1], O_RDONLY);
        objs = read_scene(fd, &obj_nmb); // scene_reader.c
        close(fd);
        printf("objs = %d\n", obj_nmb);
        //return (0);
    }
    // t_point test = get_point(2, 2, 2);
    /* float **transform_matrix;
    float *coord_matrix;

    coord_matrix = malloc(sizeof(float) * 4);
    transform_matrix = get_transform_matrix(get_three_floats(10, 0, 0), get_three_floats(0,0,0), get_three_floats(1,1,1));
    printf("point.x == %f, point.y == %f, point.z == %f\n", test.x, test.y, test.z);
    transform(&test, transform_matrix, coord_matrix, 1);
    printf("point.x == %f, point.y == %f, point.z == %f\n", test.x, test.y, test.z); */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(WID, HEI, 0, &sdl.win, &sdl.renderer);
    SDL_RenderClear(sdl.renderer);
    draw_objects(&sdl, objs, obj_nmb, light); //draw.c
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
