#include "rtv1.h"

void julia(t_sdl sdl)
{
    int		i;
	int		x;
	int		y;
    double z_re;
    double z_im;
    double new_re;
    double new_im;
    double c_re = -0.74543;
    double c_im = 0.11301;
    double zoom = 1;
	y = -1;
	while (++y < HEI)
	{
		x = -1;
		while (++x < WID)
		{
			z_re = 1.5 * (x - WID / 2) / (0.5 * zoom * WID);
            z_im = (y - HEI / 2) / (0.5 * zoom * HEI);
			i = -1;
			while (++i < 1000)
			{
				new_re = z_re * z_re;
				new_im = z_im * z_im;
				if (new_re + new_im > 4)
					break ;
				z_im = 2 * z_re * z_im + c_im;
				z_re = new_re - new_im + c_re;
			}
            SDL_SetRenderDrawColor(sdl.renderer, (uint8_t)i, (uint8_t)i, (uint8_t)i, 255);
			SDL_RenderDrawPoint(sdl.renderer, x, y);
		}
	}
    SDL_RenderPresent(sdl.renderer);
}
