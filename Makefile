# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngoulios <ngoulios@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/14 21:35:43 by ngoulios          #+#    #+#              #
#    Updated: 2025/01/14 21:54:06 by ngoulios         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc 
FLAGS = -Wall -Werror -Wextra

SRC = main.c

OBJECTS = $(SRC:.c=.o)

%.o: %.c 
	$(CC) $(FLAGS) -I. -o $@ -c $<

all: $(NAME)

$(NAME): $(OBJECTS)
	ar -rcs lib$(NAME).a $(OBJECTS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJECTS)

clean:
		rm -f $(OBJECTS)

fclean: clean
		rm -f $(NAME) lib$(NAME).a

re: fclean all

.PHONY: all clean fclean re
