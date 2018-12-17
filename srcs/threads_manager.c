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
		code |= pthread_create(&philos[i].thread, NULL, start_dinner, philos + i);
		++i;
	}
	return (code);
}

int	init_chops(t_chopstick *chops)
{
	unsigned long	i;
	int		code;

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
	int		code;

	i = 0;
	code = 0;
	while (i < PHILO_LEN)
	{
		code |= pthread_mutex_destroy(&chops[i].mutex);
		++i;
	}
	return (code);
}

void	join_threads(t_philosophers *philos)
{
	int	i;

	i = -1;
	while (++i < PHILO_LEN)
		pthread_join(philos[i].thread, NULL);
}
