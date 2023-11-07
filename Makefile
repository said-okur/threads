# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sokur <sokur@student.42kocaeli.com.tr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/25 16:59:58 by sokur             #+#    #+#              #
#    Updated: 2023/11/07 21:45:39 by sokur            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC =	philo.c\
		thats_life.c\
		controls.c\
		table.c\
		utilities.c

CFLAGS = -Wall -Wextra -Werror #-pthread -fsanitize=thread -g

RM = rm -f

all: $(NAME)

$(NAME):
	gcc $(CFLAGS) $(SRC) -o $(NAME)

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)

re: fclean all
