/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:46:42 by msrun             #+#    #+#             */
/*   Updated: 2018/12/07 18:48:36 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philosophers		g_philos[7];
t_chopstick			g_chops[7];
int					active;

void	*start_dinner(void *arg)
{
	const int index = (arg - (void*)g_philos) / sizeof(g_philos[0]);
	(void)index;
	return (NULL);
}

int		init_philos(void)
{
	unsigned long	i;
	int				code;

	code = 0;
	i = 0;
	while (i < (sizeof(g_philos) / sizeof(g_philos[0])))
	{
		g_philos[i].state = RESTING;
		g_philos[i].hp = MAX_LIFE;
		code |= pthread_create(&g_philos[i].thread, NULL, start_dinner, &g_philos[i]);
		++i;
	}
	return (code);
}

int		init_chops(void)
{
	unsigned long	i;
	int				code;

	code = 0;
	i = 0;
	while (i < (sizeof(g_chops) / sizeof(g_chops[0])))
	{
		g_chops[i].philo_index = -1;
		code |= pthread_mutex_init(&g_chops[i].mutex, NULL);
		++i;
	}
	return (code);
}

int		close_chops_mutex(void)
{
	unsigned long	i;
	int				code;

	i = 0;
	code = 0;
	while (i < (sizeof(g_chops) / sizeof(g_chops[0])))
	{
		code |= pthread_mutex_destroy(&g_chops[i].mutex);
		++i;
	}
	return (code);
}

int		main(void)
{
	if (init_chops() || init_philos())
	{
		printf("init function failed\n");
		exit(EXIT_FAILURE);
	}
	sleep(1);
	if (close_chops_mutex())
	{
		printf("close_mutex() failed\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}
