/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:29:14 by msrun             #+#    #+#             */
/*   Updated: 2018/12/07 18:48:21 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define MAX_LIFE	50
# define EAT_T		10
# define REST_T		8
# define THINK_T	5
# define TIMEOUT	120

typedef enum	e_state {
	EATING = 0,
	THINKING,
	RESTING
}				t_state;

typedef struct	s_philosophers
{
	t_state		state;
	pthread_t	thread;
	size_t		hp;
}				t_philosophers;

typedef struct	s_chopstick
{
	pthread_mutex_t	mutex;
	char			philo_index;
}				t_chopstick;

#endif
