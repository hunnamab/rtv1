/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunnamab <hunnamab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 13:38:13 by pmetron           #+#    #+#             */
/*   Updated: 2020/11/09 11:55:13 by hunnamab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	camera_left(t_scene *scene)
{
	scene->camera.rotation[1] -= 0.1;
	scene->init[scene->mode](scene);
}

void	camera_right(t_scene *scene)
{
	scene->camera.rotation[1] += 0.1;
	scene->init[scene->mode](scene);
}

void	camera_down(t_scene *scene)
{
	scene->camera.rotation[0] += 0.1;
	scene->init[scene->mode](scene);
}

void	camera_up(t_scene *scene)
{
	scene->camera.rotation[0] -= 0.1;
	scene->init[scene->mode](scene);
}

int		keyboard(t_sdl *sdl, t_scene *scene)
{
	if (SDL_PollEvent(&sdl->event))
	{
		if (SDL_QUIT == sdl->event.type || SDLK_ESCAPE == sdl->event.key.keysym.sym)
			return (0);
		if (SDLK_LEFT == sdl->event.key.keysym.sym)
		{
			SDL_RenderClear(sdl->renderer);
			camera_left(scene);
			scene->draw[scene->mode](sdl, scene);
		}
		if (SDLK_UP == sdl->event.key.keysym.sym)
		{
			SDL_RenderClear(sdl->renderer);
			camera_up(scene);
			scene->draw[scene->mode](sdl, scene);
		}
		if (SDLK_DOWN == sdl->event.key.keysym.sym)
		{
			SDL_RenderClear(sdl->renderer);
			camera_down(scene);
			scene->draw[scene->mode](sdl, scene);
		}
		if (SDLK_RIGHT == sdl->event.key.keysym.sym)
		{
			SDL_RenderClear(sdl->renderer);
			camera_right(scene);
			scene->draw[scene->mode](sdl, scene);
		}
	}
	return (1);
}
