# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/05 19:14:45 by lenygarcia        #+#    #+#              #
#    Updated: 2025/07/18 18:58:52 by lengarci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

FILES		= main.c \
			\
			init/init_player.c init/load_img.c init/load_img2.c	init/load_leny.c\
			\
			parse/convert_texture.c parse/extract_map.c parse/extract_texture.c	\
			parse/map_to_finalmap.c parse/parse_color.c parse/parse_line.c		\
			parse/parse_map.c parse/parse_texture.c parse/parsing.c				\
			parse/extract_texture2.c											\
			\
			raycast/draw_text.c raycast/draw.c raycast/raycasting_utils.c		\
			raycast/raycasting.c raycast/set_sides.c raycast/set_text.c			\
			raycast/side_text.c raycast/draw_floor_ceil.c raycast/shading.c		\
			raycast/bound_check.c raycast/get_fc_color.c raycast/dda.c			\
			raycast/draw_fc_row.c raycast/easing.c	raycast/draw_leny.c			\
			raycast/draw_leny2.c												\
			\
			controls/key_hook.c controls/key_manage.c controls/mouse_control.c	\
			controls/mouse_rotate.c controls/move_player.c controls/os_mouse.c	\
			controls/os.c controls/smooth_controls.c controls/move_utils.c		\
			\
			utils/destroy_game.c utils/failure.c utils/singleton.c				\
			utils/utils_sprite.c utils/utils.c									\
			\
			server/connect.c server/join_read.c server/join_server.c			\
			server/server_thread.c server/server_utils.c server/join_thread.c	\
			server/server.c														\
			\
			features/death_menu.c features/pause_menu.c features/shoot.c		\
			features/sprint.c features/sprite_simple.c							\
			features/world_to_screen.c features/hit_player.c features/minimap.c	\
			features/minimap_draw.c features/minimap_utils.c
SRC_DIR		= srcs
SRCS		= $(addprefix $(SRC_DIR)/, $(FILES))
OBJ_DIR		= .obj
OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)

HEADERS		= includes/cub3d.h

NAME		= cub3D

UNAME_S		= $(shell uname -s)

ifeq ($(UNAME_S),Darwin)  # macOS
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
	MLX_DIR = ./mlx_mac
else                       # Linux
	MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lbsd
	MLX_DIR = ./mlx_linux
endif

LIBFT_PATH	= ./libft
LIBFT		= $(LIBFT_PATH)/libft.a
MLX_MAKE	= $(MAKE) -C $(MLX_DIR)

RESET		= \033[0m
GREEN		= \033[0;32m
BLUE		= \033[0;34m
YELLOW		= \033[1;33m
CYAN		= \033[0;36m
RED			= \033[0;31m

all: $(NAME)

$(NAME): $(OBJS)
	@printf "$(YELLOW)==> Compiling libft...$(RESET)\n"
	$(MAKE) -C $(LIBFT_PATH)
	@printf "$(YELLOW)==> Compiling minilibx...$(RESET)\n"
	$(MLX_MAKE)
	@printf "$(GREEN)==> Linking $(NAME)...$(RESET)\n"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(MLX_FLAGS)
	@printf "$(GREEN)✔ Build complete!$(RESET)\n"

$(OBJ_DIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	@printf "$(CYAN)Compiling $<...$(RESET)\n"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_PATH) clean
	@$(MAKE) -C $(MLX_DIR) clean
	@printf "$(BLUE)✔ Clean complete.$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@printf "$(BLUE)✔ Full clean complete.$(RESET)\n"

re: fclean all


.PHONY: all clean fclean re
