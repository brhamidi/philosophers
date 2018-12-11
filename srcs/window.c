/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 14:30:55 by msrun             #+#    #+#             */
/*   Updated: 2018/12/10 19:26:28 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_sdl	init()
{
	t_sdl	sdl;

	sdl.window = SDL_CreateWindow("Philosophers", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, 1000, 1000, 0);
	sdl.renderer = SDL_CreateRenderer(sdl.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_RenderPresent(sdl.renderer);
	return (sdl);
}

void	renderer(t_sdl sdl, t_philosophers *philos)
{
	int					i;
	SDL_Surface	*image = SDL_LoadBMP("aristote.bmp");
	SDL_Texture	*texture = SDL_CreateTextureFromSurface(sdl.renderer, image);
	image = SDL_LoadBMP("baguette.bmp");
	SDL_Texture *texture_b = SDL_CreateTextureFromSurface(sdl.renderer, image);

	i = -1;
	(void)philos;
	while (++i < PHILO_LEN)
	{
		SDL_Rect dstrect = { 50 + i * 130, 100, 60, 60 };
		SDL_RenderCopy(sdl.renderer, texture, NULL, &dstrect);
		SDL_Rect dstrect2 = { 10 + i * 130, 100, 10, 60 };
		SDL_RenderCopy(sdl.renderer, texture_b, NULL, &dstrect2);
	}
	SDL_RenderPresent(sdl.renderer);
	SDL_Event event;
	char quit = 0;
	while (!quit)
	{
		SDL_WaitEvent(&event);

		switch (event.type)
		{
			case SDL_QUIT:
				quit = 1;
				break;
		}
	}

}

void	stop_window(t_sdl sdl)
{
//	SDL_DestroyTexture(texture);
//	SDL_FreeSurface(image);
	SDL_DestroyRenderer(sdl.renderer);
	SDL_DestroyWindow(sdl.window);
	SDL_Quit();


}
