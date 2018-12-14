# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/20 19:05:42 by bhamidi           #+#    #+#              #
#    Updated: 2018/12/12 16:28:38 by msrun            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	= gcc
NAME	= philo
COFLAGS	= -Werror -Wextra -Wall
COFLAGS	+= -I $$HOME/.brew/include
COFLAGS	+= -O2
CFLAGS	= $(COFLAGS) -L $$HOME/.brew/lib -lSDL2 -lSDL2_ttf
CFLAGS	+= -pthread

SRC_PATH	= srcs/
INCLUDE_PATH	= includes/

OBJ		= main.o threads_manager.o philos.o window.o

INCLUDE	= philosophers.h

OBJS=$(addprefix $(SRC_PATH), $(OBJ))
INCLUDES=$(addprefix $(INCLUDE_PATH), $(INCLUDE))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $@

$(SRC_PATH)%.o: $(SRC_PATH)%.c $(INCLUDES) Makefile
	$(CC) $(COFLAGS) -I $(INCLUDE_PATH) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all fclean clean re
