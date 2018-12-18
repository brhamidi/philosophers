/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:46:42 by msrun             #+#    #+#             */
/*   Updated: 2018/12/18 13:02:24 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		g_active;

const char	*str_of_state(t_state state)
{
	const char *tab[3] = {
		"EATING",
		"THINKING",
		"RESTING"
	};

	return (tab[state]);
}

void		decrease_life(t_philosophers *philos)
{
	int	i;

	i = -1;
	while (++i < PHILO_LEN)
		if (philos[i].state != EATING)
			if (!(--philos[i].hp))
				g_active = 0;
}

void		looping(t_philosophers *philos, t_chopstick *chops,
		const t_sdl sdl)
{
	int			time;
	SDL_Event	event;

	time = 0;
	while (g_active > 0 && time++ < TIMEOUT)
	{
		print_philos_sdl(sdl, philos, chops);
		sleep(1);
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
				g_active = -1;
	}
	print_philos_sdl(sdl, philos, chops);
	if (g_active >= 0)
	{
		if (time > TIMEOUT)
			write(1, "Now, it is time... To DAAAAAAAANCE ! ! !\n", 41);
		else
			write(1, "FAILED\n", 8);
		g_active = 0;
		while (SDL_WaitEvent(&event) && event.type != SDL_KEYDOWN)
			;
	}
}

void		run(t_philosophers *philos, t_chopstick *chops)
{
	const t_sdl	sdl = init();

	if (!check_data(sdl.data))
		return ;
	SDL_SetRenderDrawColor(sdl.renderer, 255, 255, 255, 255);
	SDL_RenderClear(sdl.renderer);
	looping(philos, chops, sdl);
	stop_window(sdl);
}

int			main(void)
{
	t_philosophers	philos[PHILO_LEN];
	t_chopstick		chops[PHILO_LEN];

	if (PHILO_LEN > 12)
	{
		write(2, "PHILO_LEN too hight\n", 20);
		exit(EXIT_SUCCESS);
	}
	g_active = 1;
	if (init_chops(chops) || init_philos(chops, philos))
		exit(EXIT_FAILURE);
	run(philos, chops);
	if (close_chops_mutex(chops))
		exit(EXIT_FAILURE);
	return (0);
}
