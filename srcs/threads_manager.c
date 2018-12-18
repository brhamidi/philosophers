/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 12:34:52 by msrun             #+#    #+#             */
/*   Updated: 2018/12/18 12:35:20 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philos(t_chopstick *chops, t_philosophers *philos)
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
		code |= pthread_create(&philos[i].thread, NULL, start_dinner,
				philos + i);
		++i;
	}
	return (code);
}

int	init_chops(t_chopstick *chops)
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

int	close_chops_mutex(t_chopstick *chops)
{
	unsigned long	i;
	int				code;

	i = 0;
	code = 0;
	while (i < PHILO_LEN)
	{
		code |= pthread_mutex_destroy(&chops[i].mutex);
		++i;
	}
	return (code);
}
