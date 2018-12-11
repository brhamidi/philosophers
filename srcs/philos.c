
#include "philosophers.h"

extern int g_active;

void	*start_dinner(void *arg)
{
	t_philosophers *philo;

	philo = (t_philosophers *)arg;
	(void)philo;
	while (1)
	{
		if (g_active == 0)
			break;
		/*
		if (try_eat())
		{
			if (try_think())
				rest();
		}
		rest();
		*/
	}
	return (NULL);
}
