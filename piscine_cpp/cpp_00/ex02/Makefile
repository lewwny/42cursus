# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/13 17:08:57 by lenygarcia        #+#    #+#              #
#    Updated: 2025/06/14 17:30:00 by lenygarcia       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = account
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -IAccount.hpp

SRCS = tests.cpp acount.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all