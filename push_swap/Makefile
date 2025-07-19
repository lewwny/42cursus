# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lenygarcia <marvin@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 20:35:06 by lenygarcia        #+#    #+#              #
#    Updated: 2025/05/05 17:18:55 by lenygarcia       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
CFLAGS		= -Wall -Wextra -Werror -g -Ilibft/includes -Iincludes
SRCS		= srcs/push_swap.c srcs/test_error.c srcs/lst_func.c srcs/stack_func1.c \
		srcs/stack_func2.c srcs/push_swap_index.c srcs/push_swap_index2.c \
		srcs/chunk_management.c srcs/back_a.c srcs/stack_func3.c srcs/sort_lil.c
OBJS		= $(SRCS:.c=.o)
NAME		= push_swap
LIBFT_PATH	= ./libft
LIBFT		= $(LIBFT_PATH)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
