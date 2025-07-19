# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lenygarcia <marvin@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/07 14:49:00 by lenygarcia        #+#    #+#              #
#    Updated: 2025/05/19 10:31:30 by lengarci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

CC    		= cc
CFLAGS		= -Wall -Wextra -Werror -g

RESET 		= \033[0m
GREEN 		= \033[0;32m
BLUE   		= \033[0;34m
YELLOW		= \033[1;33m

SRCS   	 	= srcs/main.c srcs/test_error.c srcs/error.c srcs/open_file.c srcs/path.c srcs/commands.c srcs/free_func.c srcs/pipex.c
BONUS_SRCS	= bonus/main.c bonus/test_error.c bonus/error.c bonus/open_file.c \
              	bonus/path.c bonus/commands.c bonus/free_func.c bonus/pipex.c
OBJS  		= $(SRCS:.c=.o)
BONUS_OBJS	= $(BONUS_SRCS:.c=.o)
NAME  		= pipex
BONUS_NAME	= pipex_bonus
INCLUDES	= -Iincludes -Ilibft/includes
BONUS_INC	= -Ibonus/includes -Ilibft/includes
LIBFT_PATH	= ./libft
LIBFT 		= $(LIBFT_PATH)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@printf "$(GREEN)==> Linking $(NAME)$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@printf "$(GREEN)✔ Build complete!$(RESET)\n"

bonus: CFLAGS += $(BONUS_INC)
bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS) $(LIBFT)
	@printf "$(GREEN)==> Linking $(BONUS_NAME)$(RESET)\n"
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(BONUS_NAME)
	@printf "$(GREEN)✔ Bonus build complete!$(RESET)\n"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

%.o: %.c
	@printf "$(YELLOW)==> Compiling $<$(RESET)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@printf "$(BLUE)==> Cleaning objects$(RESET)\n"
	@rm -f $(OBJS) $(BONUS_OBJS)
	@$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	@printf "$(BLUE)==> Cleaning all$(RESET)\n"
	@rm -f $(NAME) $(BONUS_NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re

