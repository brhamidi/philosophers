/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 14:30:55 by msrun             #+#    #+#             */
/*   Updated: 2018/12/17 16:17:06 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

SDL_Color	get_color(unsigned char r, unsigned char g, unsigned char b,
		unsigned char s)
{
	const SDL_Color color = {r, g, b, s};

	return (color);
}

SDL_Rect	get_rect(int x, int y, int h, int w)
{
	const SDL_Rect	rect = {x, y, h, w};

	return (rect);
}

void		create_use_surface(SDL_Renderer *renderer, SDL_Surface *surface,
		SDL_Texture **texture)
{
	*texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

void		get_txt(t_sdl *sdl)
{
	TTF_Font	*font;

	TTF_Init();
	if (!(font = TTF_OpenFont("font.ttf", 10)))
	{
		TTF_Quit();
		return ;
	}
	sdl->data.color[WHITE] = get_color(255, 255, 255, 255);
	sdl->data.color[BLACK] = get_color(0, 0, 0, 0);
	sdl->data.color[RED] = get_color(255, 0, 0, 255);
	sdl->data.color[GREEN] = get_color(0, 255, 0, 255);
	sdl->data.color[BLUE] = get_color(0, 0, 255, 255);
	create_use_surface(sdl->renderer, TTF_RenderText_Shaded(font,
			str_of_state(EATING), sdl->data.color[GREEN],
			sdl->data.color[WHITE]), &sdl->data.texture_txt[EATING]);
	create_use_surface(sdl->renderer, TTF_RenderText_Shaded(font,
			str_of_state(THINKING), sdl->data.color[RED],
			sdl->data.color[WHITE]), &sdl->data.texture_txt[THINKING]);
	create_use_surface(sdl->renderer, TTF_RenderText_Shaded(font,
			str_of_state(RESTING), sdl->data.color[BLUE],
			sdl->data.color[WHITE]), &sdl->data.texture_txt[RESTING]);
	TTF_CloseFont(font);
	TTF_Quit();
}

void		get_data(t_sdl *sdl)
{
	create_use_surface(sdl->renderer, SDL_LoadBMP("assiette.bmp"),
			&sdl->data.texture[EATING]);
	create_use_surface(sdl->renderer, SDL_LoadBMP("think.bmp"),
			&sdl->data.texture[THINKING]);
	create_use_surface(sdl->renderer, SDL_LoadBMP("zzz.bmp"),
			&sdl->data.texture[RESTING]);
	create_use_surface(sdl->renderer, SDL_LoadBMP("baguette.bmp"),
			&sdl->data.texture[3]);
	create_use_surface(sdl->renderer, SDL_LoadBMP("aristote.bmp"),
			&sdl->data.texture[4]);
	get_txt(sdl);
}

t_sdl		init(void)
{
	t_sdl	sdl;

	if (PHILO_LEN <= 0)
		sdl.window = SDL_CreateWindow("Philosophers", SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED, 70, 10, 0);
	else
		sdl.window = SDL_CreateWindow("Philosophers", SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED, 10 + 132 * PHILO_LEN, 230, 0);
	sdl.renderer = SDL_CreateRenderer(sdl.window, -1, 0);
	SDL_RenderPresent(sdl.renderer);
	get_data(&sdl);
	return (sdl);
}

int			check_data(t_data data)
{
	int	i;

	i = -1;
	while (++i < 5)
		if (!data.texture[i])
		{
			write(2, "Error texture could not get loaded\n", 34);
			return (0);
		}
	i = -1;
	while (++i < 3)
		if (!data.texture_txt[i])
		{
			write(2, "Error texture_txt could not get loaded\n", 38);
			return (0);
		}
	return (1);
}

void		printer(const t_sdl sdl, t_philosophers *philos,
		t_chopstick *chops, int i)
{
	SDL_Rect	dstrect;

	dstrect = get_rect(50 + i * 130, 20, 60, 15);
	SDL_RenderCopy(sdl.renderer, sdl.data.texture_txt[philos[i].state], NULL,
			&dstrect);
	dstrect = get_rect(10 + i * 130 + (chops[i].philo_index == 1 ? 30 : 0) +
	(chops[i].philo_index == -1 ? -30 : 0), 120 +
	(chops[i].philo_index ? 0 : -70), 10, 60);
	SDL_RenderCopy(sdl.renderer, sdl.data.texture[3], NULL, &dstrect);
	dstrect = get_rect(50 + i * 130, 50, 60, 60);
	SDL_RenderCopy(sdl.renderer, sdl.data.texture[philos[i].state], NULL,
			&dstrect);
	dstrect = get_rect(50 + i * 130, 120, 60, 60);
	SDL_RenderCopy(sdl.renderer, sdl.data.texture[4], NULL, &dstrect);
	dstrect = get_rect(50 + i * 130, 180, 60 * philos[i].hp / MAX_LIFE, 10);
	SDL_SetRenderDrawColor(sdl.renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(sdl.renderer, &dstrect);
	SDL_SetRenderDrawColor(sdl.renderer, 0, 0, 0, 0);
	dstrect = get_rect(50 + i * 130, 180, 60, 10);
	SDL_RenderDrawRect(sdl.renderer, &dstrect);
	SDL_SetRenderDrawColor(sdl.renderer, 255, 255, 255, 255);
}

void		print_philos_sdl(const t_sdl sdl, t_philosophers *philos,
		t_chopstick *chops)
{
	int			i;
	SDL_Rect	dstrect;

	i = -1;
	if (PHILO_LEN > 0)
	{
		while (++i < PHILO_LEN)
			printer(sdl, philos, chops, i);
		dstrect = get_rect(10 + i * 130 + (chops[0].philo_index == 1 ? 30 : 0) +
				(chops[0].philo_index == -1 ? -30 : 0), 120 +
				(chops[0].philo_index ? 0 : -70), 10, 60);
	}
	SDL_RenderCopy(sdl.renderer, sdl.data.texture[3], NULL, &dstrect);
	SDL_RenderPresent(sdl.renderer);
	SDL_RenderClear(sdl.renderer);
}

void		stop_window(t_sdl sdl)
{
	int	i;

	i = -1;
	while (++i < 5)
		SDL_DestroyTexture(sdl.data.texture[i]);
	i = -1;
	while (++i < 3)
		SDL_DestroyTexture(sdl.data.texture_txt[i]);
	SDL_DestroyRenderer(sdl.renderer);
	SDL_DestroyWindow(sdl.window);
	SDL_Quit();
}
