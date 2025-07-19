/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:15:31 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/05/12 16:17:11 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include <fcntl.h>
# include "../minilibx/mlx.h"

# define TILE_SIZE 64

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*img_wall;
	void	*img_floor;
	void	*img_player;
	void	*img_exit;
	void	*img_exit2;
	void	*img_enemy;
	void	**img_collectible;
	char	**map;
	int		collectible_left;
	int		num_collectible_frame;
	int		current_frame;
	int		move;
	int		enemy;
}	t_game;

void	arg_error(int argc, char *file);
void	wrong_file(void);
void	malloc_error(char **map);
void	free_map(char **map);
void	parse_map(t_game *game);
void	invalid_map(char **map);
void	parse_map_char(t_game *game);
void	test_path(char **map);
void	error_mlx(t_game *game);
void	render_map(t_game *game);
void	load_images(t_game *game);
void	count_move(t_game *game);
void	success_game(t_game *game);
void	change_exit(char **map);
void	error_load(t_game *game);
void	malloc_error2(t_game *game);
void	destroy_game(t_game *game);
void	move_enemy(t_game *game, int *direction);
void	loose_game(t_game *game);
void	destroy_error(t_game *game);

int		handle_key(int key, t_game *game);
int		check_enemy(char **map);

char	**read_file(char *file);

#endif
