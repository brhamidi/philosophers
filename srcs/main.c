/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:46:42 by msrun             #+#    #+#             */
/*   Updated: 2018/12/12 17:50:26 by msrun            ###   ########.fr       */
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

void	decrease_life(t_philosophers *philos)
{
	int	i;

	i = -1;
	while (++i < PHILO_LEN)
		if (philos[i].state != EATING)
			if (!(--philos[i].hp))
				g_active = 0;
}

void	print_philos(t_philosophers *philos)
{
	int	i;

	i = -1;
	while (++i < PHILO_LEN)
	{
		printf("--------------\n");
		if (philos[i].hp == 1)
			printf("HP: \x1b[31m%ld\x1b[0m\n", philos[i].hp);
		else
			printf("HP: %ld\n", philos[i].hp);
		printf("State [%s]\n", str_of_state(philos[i].state));
	}
	printf("\n\n");
}

void	run(t_philosophers *philos, t_chopstick *chops)
{
	struct timeval	start;
	struct timeval	stop;
	int		time;

	const t_sdl		sdl = init();
	SDL_Event		event;

	(void)chops;
	time = 0;
	SDL_SetRenderDrawColor(sdl.renderer, 255, 255, 255, 255);
	SDL_RenderClear(sdl.renderer);
	while (g_active)
	{
		if (time > TIMEOUT)
			break;
		gettimeofday(&start, NULL);

		print_philos_sdl(sdl, philos, chops);
		print_philos(philos);
		++time;

		gettimeofday(&stop, NULL);
		usleep(500000);
//		sleep(1);
		while (SDL_PollEvent(&event))
			switch (event.type)
			{
				case SDL_QUIT:
					g_active = -1;
					break ;
			}
	}
	print_philos_sdl(sdl, philos, chops);
	print_philos(philos);
	if (time > TIMEOUT)
		write(1, "SUCESS\n", 8);
	else
		write(1, "FAILED\n", 8);
	read(0, NULL, 1);
}

int	main(void)
{
	t_philosophers		philos[PHILO_LEN];
	t_chopstick		chops[PHILO_LEN];

	g_active = 1;
	if (init_chops(chops) || init_philos(chops, philos))
		exit(EXIT_FAILURE);
	run(philos, chops);
	if (close_chops_mutex(chops))
		exit(EXIT_FAILURE);
	join_threads(philos);
	return (0);
}
