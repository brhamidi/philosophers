/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 14:30:55 by msrun             #+#    #+#             */
/*   Updated: 2018/12/12 17:29:22 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_sdl	init()
{
	t_sdl	sdl;

	sdl.window = SDL_CreateWindow("Philosophers", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, 1000, 230, 0);
	sdl.renderer = SDL_CreateRenderer(sdl.window, -1, 0);
	SDL_RenderPresent(sdl.renderer);
	return (sdl);
}

void	print_philos_sdl(const t_sdl sdl, t_philosophers *philos, t_chopstick *chops)
{
	int					i;
	SDL_Surface	*image = SDL_LoadBMP("aristote.bmp");
	SDL_Texture	*texture = SDL_CreateTextureFromSurface(sdl.renderer, image);
	image = SDL_LoadBMP("baguette.bmp");
	SDL_Texture *texture_b = SDL_CreateTextureFromSurface(sdl.renderer, image);
	TTF_Init();
	TTF_Font	*font;
	font = TTF_OpenFont("font.ttf", 10);
	SDL_Surface	*text_surface;
	SDL_Color	white = {255,255,255,255};
	SDL_Color	black = {0,0,0,255};
	SDL_Texture *txt;

	i = -1;
	(void)philos;
	(void)chops;
	while (++i < PHILO_LEN)
	{
		text_surface = TTF_RenderText_Shaded(font, str_of_state(philos[i].state), black, white);
		txt = SDL_CreateTextureFromSurface(sdl.renderer, text_surface);
		SDL_Rect mesrect = {50 + i * 130, 20, 60, 15};
		SDL_RenderCopy(sdl.renderer, txt, NULL, &mesrect);

		SDL_Rect dstrect = { 50 + i * 130, 50, 60, 60 };
		SDL_RenderCopy(sdl.renderer, texture, NULL, &dstrect);

		SDL_Rect dstrect2 = { 10 + i * 130, 50 + (chops[i].philo_index ? 0 : 70), 10, 60 };
		SDL_RenderCopy(sdl.renderer, texture_b, NULL, &dstrect2);
	}
	SDL_Rect dstrect2 = { 10 + i * 130, 50 + (chops[0].philo_index ? 0 : 70), 10, 60 };
	SDL_RenderCopy(sdl.renderer, texture_b, NULL, &dstrect2);
	SDL_RenderPresent(sdl.renderer);
	SDL_RenderClear(sdl.renderer);

	i = -1;
	while (++i < PHILO_LEN)
	{
		printf("--------------\n");
		printf("HP: %ld\n", philos[i].hp);
		printf("State [%s]\n", str_of_state(philos[i].state));
	}
	TTF_CloseFont(font);
	printf("\n\n");
}

void	stop_window(t_sdl sdl)
{
//	SDL_DestroyTexture(texture);
//	SDL_FreeSurface(image);
//	TTF_CloseFont();
//	TTF_Quit();
	SDL_DestroyRenderer(sdl.renderer);
	SDL_DestroyWindow(sdl.window);
	SDL_Quit();
}
