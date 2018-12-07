/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:29:14 by msrun             #+#    #+#             */
/*   Updated: 2018/12/07 15:57:08 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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
	t_philosophers	*current;
}				t_chopstick;

#endif
