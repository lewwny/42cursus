# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 20:35:06 by lengarci          #+#    #+#              #
#    Updated: 2025/04/30 17:00:46 by lenygarcia       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	= cc -g
CFLAGS	= -Wall -Wextra -Werror
SRCS	= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c \
	  ft_toupper.c ft_tolower.c ft_printf.c \
	  ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strnstr.c ft_atoi.c \
	  ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
	  ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	  ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
	  ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c get_next_line.c \
	  ft_putchari.c ft_putnbri.c ft_putstri.c ft_putnbrui.c ft_putptr.c ft_putnbrhexmaj.c \
	  ft_putnbrhexmin.c
HEADERS	= libft.h
OBJS	= ${SRCS:.c=.o}
NAME	= libft.a

all: ${NAME}

$(NAME): $(OBJS)
	@ar rcs $(NAME) $^

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re:	fclean all
