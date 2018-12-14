/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:29:14 by msrun             #+#    #+#             */
/*   Updated: 2018/12/14 15:48:02 by msrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <sys/time.h>

# define MAX_LIFE	5
# define EAT_T		1
# define REST_T		1
# define THINK_T	1
# define TIMEOUT	60
# define PHILO_LEN	7


typedef enum	e_color
{
	WHITE = 0,
	BLACK,
	RED,
	GREEN,
	BLUE
}				t_color;

typedef enum	e_state
{
	EATING = 0,
	THINKING,
	RESTING
}				t_state;

typedef struct	s_chopstick
{
	pthread_mutex_t	mutex;
	char		philo_index;
}				t_chopstick;

typedef struct	s_philosophers
{
	t_state		state;
	pthread_t	thread;
	size_t		hp;
	t_chopstick	*chopstick_left;
	t_chopstick	*chopstick_right;
}				t_philosophers;

typedef struct	s_data
{
	SDL_Texture		*texture[5];
	SDL_Texture		*texture_txt[3];
	SDL_Color		color[5];
}				t_data;

typedef struct	s_sdl
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	t_data			data;
}				t_sdl;

void	stop_window(t_sdl sdl);
void	renderer(t_sdl, t_philosophers*);
t_sdl	init();
void	print_philos(t_philosophers*);
void	print_philos_sdl(const t_sdl, t_philosophers*, t_chopstick*);
int		check_data(t_data data);

const char	*str_of_state(t_state state);
void	*start_dinner(void *arg);
int	init_philos(t_chopstick *chops, t_philosophers *philos);
int	init_chops(t_chopstick *chops);
int	close_chops_mutex(t_chopstick *chops);
void	join_threads(t_philosophers *philos);

#endif
