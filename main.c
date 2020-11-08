/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunnamab <hunnamab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 15:39:02 by hunnamab          #+#    #+#             */
/*   Updated: 2020/11/08 16:14:27 by hunnamab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void check_mode(int as, char **av, int *mode)
{
	if (as == 2 || (as == 3 && (ft_strequ(av[2], "default"))))
	 	*mode = 0;
	else if (as == 3 && (ft_strequ(av[2], "normal")))
	 	*mode = 1;
	else if (as == 3 && (ft_strequ(av[2], "depth")))
		*mode = 2;
	else if (as == 3 && (ft_strequ(av[2], "flat_light")))
		*mode = 3;
}

void output_description()
{
	ft_putstr("usage: ./rtv1 [scene_file] [mode]\n\n");
	ft_putstr("mode is an optional argument, it should be [default], [normal], [depth] or [flat_light]\n");
	ft_putstr("\t1. default or no argument after scene file's name means the program draws the usual scene\n");
	ft_putstr("\t2. normal means the program draws a normal map of scene's objects\n");
	ft_putstr("\t3. depth mode draws a depth map of the scene's objects\n");
	ft_putstr("\t4. flat_light can draw a scene with no shadows or shiny effect from light sources\n");
}

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
		output_description();
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
		//return (0);
	}
	check_mode(args, argv, &scene->mode);
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindowAndRenderer(WID, HEI, 0, &sdl.win, &sdl.renderer);
	SDL_RenderClear(sdl.renderer);
	init_scene(scene);
	(scene->mode == 0) ? draw_scene(&sdl, scene) : draw_normal_buf(&sdl, scene);
	while (k)
		k = keyboard(&sdl, scene);
	clear_scene(scene);
	SDL_DestroyRenderer(sdl.renderer);
	SDL_DestroyWindow(sdl.win);
	SDL_Quit();
	return (0);
}
