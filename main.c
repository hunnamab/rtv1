/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunnamab <hunnamab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 15:39:02 by hunnamab          #+#    #+#             */
/*   Updated: 2020/11/09 11:57:07 by hunnamab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	check_mode(int as, char **av, int *mode)
{
	if (as == 2 || (as == 3 && (ft_strequ(av[2], "default"))))
		*mode = 0;
	else if (as == 3 && (ft_strequ(av[2], "normal")))
		*mode = 1;
	else if (as == 3 && (ft_strequ(av[2], "depth")))
		*mode = 2;
	else if (as == 3 && (ft_strequ(av[2], "raycast")))
		*mode = 3;
}

int		main(int args, char **argv)
{
	int			fd;
	t_sdl		sdl;
	t_object	**buf;
	t_scene		*scene;
	int			k;

	k = 1;
	scene = (t_scene *)protected_malloc(sizeof(t_scene), 1);
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
	scene->draw[scene->mode](&sdl, scene);
	while (k)
		k = keyboard(&sdl, scene);
	scene->clean[scene->mode](scene);
	SDL_DestroyRenderer(sdl.renderer);
	SDL_DestroyWindow(sdl.win);
	SDL_Quit();
	return (0);
}
