# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/22 18:09:43 by ebednar           #+#    #+#              #
#    Updated: 2020/11/22 19:59:34 by ebednar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_one
SRC =	./src/main.c \
		./src/utils.c \
		./src/print.c
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