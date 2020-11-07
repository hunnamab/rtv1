/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunnamab <hunnamab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 15:39:02 by hunnamab          #+#    #+#             */
/*   Updated: 2020/11/07 22:37:24 by hunnamab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int main(int args, char **argv)
{
	int			fd;
	t_sdl		sdl;
	t_object	**buf;
	t_scene		*scene;
	int			k;

	k = 1;
	scene = malloc(sizeof(t_scene));
	if (args < 2 || args > 3)
	{
		ft_putstr("usage: ./rtv1 [scene_file] [mode]\n\n");
		ft_putstr("mode is an optional argument, it should be [default] or [normal]\n");
		ft_putstr("\tdefault or no argument after scene file's name means the program draws the usual scene\n");
		ft_putstr("\tnormal means the program draws a normal map of scene's objects\n");
		return (0);
	}
	else
	{
		fd = open(argv[1], O_RDONLY);
		buf = read_scene(fd, scene); // scene_reader.c
		close(fd);
		printf("obj_nmb = %d\n", scene->obj_nmb);
		printf("light_nmb = %d\n", scene->light_nmb);
		scene->objs = get_objects_structures(scene->obj_nmb, buf); // get_structures.c
		scene->light = get_light_structures(scene->light_nmb, buf); // get_structures.c
		return (0);
	}
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindowAndRenderer(WID, HEI, 0, &sdl.win, &sdl.renderer);
	SDL_RenderClear(sdl.renderer);
	init_scene(scene);
	if (args == 2 || (args == 3 && (ft_strcmp(argv[2], "default") == 0)))
	 	draw_scene(&sdl, scene);
	else if (args == 3 && (ft_strequ(argv[2], "normal")))
	 	draw_normal_buf(&sdl, scene);
	while (k)
	{
		k = keyboard(&sdl, scene);
	}
	clear_scene(scene);
	SDL_DestroyRenderer(sdl.renderer);
	SDL_DestroyWindow(sdl.win);
	SDL_Quit();
	return (0);
}
