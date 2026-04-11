# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hiipek <hiipek@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/30 18:23:10 by hiipek            #+#    #+#              #
#    Updated: 2024/12/02 15:09:43 by hiipek           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = ft_printf.c ft_printf_func.c

OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

RM = rm -f
CC = cc

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

ft_printf.o: ft_printf.c
	$(CC) $(FLAGS) -c ft_printf.c -o ft_printf.o

ft_printf_func.o: ft_printf_func.c
	$(CC) $(FLAGS) -c ft_printf_func.c -o ft_printf_func.o

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all