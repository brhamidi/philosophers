
#include "philosophers.h"

extern int g_active;

void	sleep_decrease(int n, int decrease, t_philosophers *philo)
{
	if (n > 0)
	{
		usleep(200000);
		if (decrease)
			if (!(--philo->hp))
				g_active = 0;
		sleep_decrease(n - 1, decrease, philo);
	}
}

void	rest(t_philosophers *philo)
{
	philo->state = RESTING;
	sleep_decrease(REST_T, 1, philo);
}

int	eat(t_philosophers *philo)
{
	if (pthread_mutex_trylock(& philo->chopstick_left->mutex))
		return (1);
	if (pthread_mutex_trylock(& philo->chopstick_right->mutex))
	{
		pthread_mutex_unlock(& philo->chopstick_left->mutex);
		return (1);
	}
	philo->state = EATING;
	sleep_decrease(EAT_T, 0, philo);
	philo->hp = MAX_LIFE;
	pthread_mutex_unlock(& philo->chopstick_right->mutex);
	pthread_mutex_unlock(& philo->chopstick_left->mutex);
	return (0);
}

int	think(t_philosophers *philo)
{
	pthread_mutex_t		*mutex;

	mutex = & philo->chopstick_left->mutex;
	if (pthread_mutex_trylock(& philo->chopstick_left->mutex))
	{
		if (pthread_mutex_trylock(& philo->chopstick_right->mutex))
			return (1);
		mutex = & philo->chopstick_right->mutex;
	}
	pthread_mutex_unlock(mutex);
	philo->state = THINKING;
	sleep_decrease(THINK_T, 1, philo);
	return (0);
}

void	*start_dinner(void *arg)
{
	t_philosophers *philo;

	philo = (t_philosophers *)arg;
	while (g_active)
	{
		if (eat(philo) && eat(philo))
		{
			if (think(philo))
				rest(philo);
			return (start_dinner(arg));
		}
		rest(philo);
		if (think(philo))
			rest(philo);
	}
	return (NULL);
}
