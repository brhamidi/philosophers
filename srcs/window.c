/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 14:30:55 by msrun             #+#    #+#             */
/*   Updated: 2018/12/18 12:55:04 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_sdl		init(void)
{
	t_sdl	sdl;

	if (PHILO_LEN <= 0)
		sdl.window = SDL_CreateWindow("Philosophers", SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED, 70, 10, 0);
	else
		sdl.window = SDL_CreateWindow("Philosophers", SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED, 13 + 132 * PHILO_LEN, 230, 0);
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
