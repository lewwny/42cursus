# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/25 11:17:35 by lengarci          #+#    #+#              #
#    Updated: 2025/09/23 11:20:39 by lengarci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME		=	webserv
CC			=	g++
CFLAGS		=	-Wall -Wextra -Werror -std=c++98 -g3
RM			=	rm -f
DIR_OBJ		=	.obj/
SRCS		=	main.cpp \
				src/Server.cpp \
				src/Request.cpp \
				src/Parser.cpp	\
				src/Response.cpp \
				src/Router.cpp \
				src/ConfigParse.cpp \
				src/ServerManager.cpp \
				src/Config.cpp \
				src/StaticExec.cpp \
				src/Upload.cpp \
				src/CGI.cpp \
				src/Cookie.cpp \
				src/AutoIndex.cpp
OBJS		=	$(addprefix $(DIR_OBJ), $(SRCS:.cpp=.o))
HEADER		=	include/Server.hpp \
				include/Request.hpp \
				include/Parser.hpp \
				include/Response.hpp \
				include/Router.hpp \
				include/ConfigParse.hpp \
				include/ServerManager.hpp \
				include/Config.hpp \
				include/StaticExec.hpp \
				include/Upload.hpp \
				include/CGI.hpp \
				include/Cookie.hpp \
				include/AutoIndex.hpp

all:		$(NAME) PIP_GENAI

$(NAME):	$(OBJS)
		$(CC) $(CFLAGS) -o $@ $^
		@printf "\033[0;32m$(NAME) created\033[0m\n"

$(DIR_OBJ)%.o:	%.cpp $(HEADER)
		@mkdir -p $(dir $@)
		$(CC) $(CFLAGS) -c $< -o $@
		@printf "\033[0;34mCompiled:\033[0m $<\n"

PIP_GENAI:
	@if ! python3 -c "import google.genai" 2>/dev/null; then \
		pip install google.genai; \
		printf "\033[0;32mgoogle.genai installed\033[0m\n"; \
	fi

clean:
		$(RM) -r $(DIR_OBJ)
		$(RM) 
		@printf "\033[0;32mObject files removed\033[0m\n"

fclean:		clean
		$(RM) $(NAME)
		@printf "\033[0;32m$(NAME) removed\033[0m\n"

re:	fclean
		@make all --silent
