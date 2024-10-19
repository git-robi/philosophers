# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 13:20:44 by rgiambon          #+#    #+#              #
#    Updated: 2024/10/19 11:22:35 by rgiambon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread
SRCS = philo.c checks.c init.c routine.c monitor.c utils.c
OBJS = $(SRCS:.c=.o)
HEADER = philo.h

all: $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@chmod +x $(NAME)

%.o: %.c Makefile $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
