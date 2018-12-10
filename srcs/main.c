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

void	*start_dinner(void *arg)
{
	const t_philosophers *philo = (t_philosophers *)arg;

	printf("%zu\n", philo->hp);
	return (NULL);
}

int		init_philos(t_chopstick *chops, t_philosophers *philos)
{
	int	i;
	int	code;

	code = 0;
	i = 0;
	while (i < PHILO_LEN)
	{
		philos[i].state = RESTING;
		philos[i].hp = MAX_LIFE;
		philos[i].chopstick_left = chops + i;
		philos[i].chopstick_right = &chops[i + 1 == PHILO_LEN ? 0 : i + 1];
		code |= pthread_create(&philos[i].thread, NULL, start_dinner, philos + i);
		++i;
	}
	return (code);
}

int		init_chops(t_chopstick *chops)
{
	unsigned long	i;
	int				code;

	code = 0;
	i = 0;
	while (i < PHILO_LEN)
	{
		chops[i].philo_index = -1;
		code |= pthread_mutex_init(&chops[i].mutex, NULL);
		++i;
	}
	return (code);
}

int		close_chops_mutex(t_chopstick *chops)
{
	unsigned long	i;
	int				code;

	i = 0;
	code = 0;
	while (i < PHILO_LEN)
	{
	//	pthread_mutex_unlock(g_chops[i].mutex);
		code |= pthread_mutex_destroy(&chops[i].mutex);
		++i;
	}
	return (code);
}

int		main(void)
{
	t_philosophers		philos[PHILO_LEN];
	t_chopstick			chops[PHILO_LEN];

	if (init_chops(chops) || init_philos(chops, philos))
	{
		printf("init function failed\n");
		exit(EXIT_FAILURE);
	}
	sleep(1);
	if (close_chops_mutex(chops))
	{
		printf("close_mutex() failed\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}
