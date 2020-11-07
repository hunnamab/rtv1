/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunnamab <hunnamab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 13:38:13 by pmetron           #+#    #+#             */
/*   Updated: 2020/11/07 19:46:48 by hunnamab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	camera_left(t_scene *scene)
{
	double	**matrix;
	int		x;

	x = 0;
	matrix = rotate_y(-0.1);
	while (x < WID * HEI)
	{
		transform(&scene->ray_buf[x].dir, matrix, 1);
		x++;
	}
	get_closest_points(scene);
	get_intersection_buf(scene);
	get_normal_buf(scene);
	get_material_buf(scene);
	free(matrix);
}

void	camera_right(t_scene *scene)
{
	double	**matrix;
	int		x;

	x = 0;
	matrix = rotate_y(0.1);
	while (x < WID * HEI)
	{
		transform(&scene->ray_buf[x].dir, matrix, 1);
		x++;
	}
	get_closest_points(scene);
	get_intersection_buf(scene);
	get_normal_buf(scene);
	get_material_buf(scene);
	free(matrix);
}

void	camera_down(t_scene *scene)
{
	double	**matrix;
	int		x;

	x = 0;
	matrix = rotate_x(0.1);
	while (x < WID * HEI)
	{
		transform(&scene->ray_buf[x].dir, matrix, 1);
		x++;
	}
	get_closest_points(scene);
	get_intersection_buf(scene);
	get_normal_buf(scene);
	get_material_buf(scene);
	free(matrix);  
}

void	camera_up(t_scene *scene)
{
	double	**matrix;
	int		x;

	x = 0;
	matrix = rotate_x(-0.1);
	while (x < WID * HEI)
	{
		transform(&scene->ray_buf[x].dir, matrix, 1);
		x++;
	}
	get_closest_points(scene);
	get_intersection_buf(scene);
	get_normal_buf(scene);
	get_material_buf(scene);
	free(matrix);  
}

int		keyboard(t_sdl *sdl, t_scene *scene)
{
	if (SDL_PollEvent(&sdl->event))
	{
		if (SDL_QUIT == sdl->event.type || SDLK_ESCAPE == sdl->event.key.keysym.sym)
			return(0);
		if (SDLK_LEFT == sdl->event.key.keysym.sym)
		{
			SDL_RenderClear(sdl->renderer);
			camera_left(scene);
			draw_scene(sdl, scene);
		}
		if (SDLK_UP == sdl->event.key.keysym.sym)
		{
			SDL_RenderClear(sdl->renderer);
			camera_up(scene);
			draw_scene(sdl, scene);
		}
		if (SDLK_DOWN == sdl->event.key.keysym.sym)
		{
			SDL_RenderClear(sdl->renderer);
			camera_down(scene);
			draw_scene(sdl, scene);
		}
		if (SDLK_RIGHT == sdl->event.key.keysym.sym)
		{
			SDL_RenderClear(sdl->renderer);
			camera_right(scene);
			draw_scene(sdl, scene);
		}
	}
	return (1);
}
