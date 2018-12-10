# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/20 19:05:42 by bhamidi           #+#    #+#              #
#    Updated: 2018/12/10 13:13:26 by msrun            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	= gcc
NAME	= philo
CFLAGS	= -Werror -Wextra -Wall
CFLAGS	+= -O2
CFLAGS	+= -pthread

SRC_PATH	= srcs/
INCLUDE_PATH	= includes/

OBJ		= main.o threads_manager.o philos.o

INCLUDE	= philosophers.h

OBJS=$(addprefix $(SRC_PATH), $(OBJ))
INCLUDES=$(addprefix $(INCLUDE_PATH), $(INCLUDE))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $@

$(SRC_PATH)%.o: $(SRC_PATH)%.c $(INCLUDES) Makefile
	$(CC) $(CFLAGS) -I $(INCLUDE_PATH) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all fclean clean re
