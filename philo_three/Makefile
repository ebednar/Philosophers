# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/22 18:09:43 by ebednar           #+#    #+#              #
#    Updated: 2020/12/20 19:42:12 by ebednar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_three
SRC =	./src/main.c \
		./src/cycle.c \
		./src/observer.c \
		./src/timer.c \
		./src/utils.c \
		./src/print.c \
		./src/sem_init.c \
		./src/fork_process.c
OBJECTS = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -Werror
INCLUDES = -I include

all: $(NAME)

$(NAME): $(OBJECTS)
	gcc $(FLAGS) $(INCLUDES) $(OBJECTS) -o $(NAME)

%.o: %.c
	gcc $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	/bin/rm -f $(OBJECTS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all