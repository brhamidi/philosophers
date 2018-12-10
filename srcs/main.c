/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:46:42 by msrun             #+#    #+#             */
/*   Updated: 2018/12/10 13:18:14 by msrun            ###   ########.fr       */
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
			if (!(philos[i].hp--))
				g_active = 0;
}

void	print_philos(t_philosophers *philos)
{
	int	i;

	i = -1;
	while (++i < PHILO_LEN)
	{
		printf("--------------\n");
		printf("HP: %ld\n", philos[i].hp);
		printf("State [%s]\n", str_of_state(philos[i].state));
	}
	printf("\n\n");
}

void	run(t_philosophers *philos)
{
	struct timeval	start;
	struct timeval	stop;
	float 		time;

	time = 0.0;
	while (g_active)
	{
		gettimeofday(&start, NULL);

		//compute
		time += 1.0;
		print_philos(philos);
		decrease_life(philos);
		//end of compute

		gettimeofday(&stop, NULL);
		sleep(1);
	}
	read(0, NULL, 1);
}

int	main(void)
{
	t_philosophers		philos[PHILO_LEN];
	t_chopstick		chops[PHILO_LEN];

	if (init_chops(chops) || init_philos(chops, philos))
		exit(EXIT_FAILURE);
	g_active = 1;
	run(philos);
	if (close_chops_mutex(chops))
		exit(EXIT_FAILURE);
	return (0);
}
