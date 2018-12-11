
#include "philosophers.h"

extern int g_active;

int	try_eat(t_philosophers *philo)
{
	if (pthread_mutex_trylock(& philo->chopstick_left->mutex))
		return (1);
	if (pthread_mutex_trylock(& philo->chopstick_right->mutex))
	{
		pthread_mutex_unlock(& philo->chopstick_right->mutex);
		return (1);
	}
	philo->state = EATING;
	sleep(EAT_T);
	philo->hp = MAX_LIFE;
	pthread_mutex_unlock(& philo->chopstick_right->mutex);
	pthread_mutex_unlock(& philo->chopstick_left->mutex);
	return (0);
}

int	try_think(t_philosophers *philo)
{
	pthread_mutex_t		*mutex;

	if (pthread_mutex_trylock(& philo->chopstick_left->mutex))
	{
		if (pthread_mutex_trylock(& philo->chopstick_right->mutex))
			return (1);
		mutex = & philo->chopstick_right->mutex;
	}
	mutex = & philo->chopstick_left->mutex;
	pthread_mutex_unlock(mutex);
	philo->state = THINKING;
	sleep(THINK_T);
	return (0);
}

void	rest(t_philosophers *philo)
{
	philo->state = RESTING;
	sleep(REST_T);
}

void	*start_dinner(void *arg)
{
	t_philosophers *philo;

	philo = (t_philosophers *)arg;
	while (1)
	{
		if (g_active == 0)
			break;
		if (try_eat(philo))
		{
			if (try_think(philo))
				rest(philo);
			try_eat(philo);
		}
		rest(philo);
	}
	return (NULL);
}
