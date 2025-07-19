/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:48:30 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/05/12 12:02:39 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	find_player(char **map, int *y, int *x)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
			{
				*y = i;
				*x = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

static void	take_collectible(t_game *game, int new_y, int new_x)
{
	game->map[new_y][new_x] = '0';
	if (--game->collectible_left == 0)
		change_exit(game->map);
}

static void	move_player(t_game *game, int next_y, int next_x)
{
	int	player_x;
	int	player_y;
	int	new_x;
	int	new_y;

	find_player(game->map, &player_y, &player_x);
	new_x = player_x + next_x;
	new_y = player_y + next_y;
	if (game->map[new_y][new_x] == '1' || game->map[new_y][new_x] == 'E')
		return ;
	if (game->map[new_y][new_x] == 'e')
	{
		success_game(game);
		return ;
	}
	if (game->map[new_y][new_x] == 'M')
		loose_game(game);
	if (game->map[new_y][new_x] == 'C')
		take_collectible(game, new_y, new_x);
	count_move(game);
	game->map[player_y][player_x] = '0';
	game->map[new_y][new_x] = 'P';
	render_map(game);
}

int	handle_key(int key, t_game *game)
{
	if (key == 119)
		move_player(game, -1, 0);
	if (key == 115)
		move_player(game, 1, 0);
	if (key == 97)
		move_player(game, 0, -1);
	if (key == 100)
		move_player(game, 0, 1);
	if (key == 65307)
	{
		destroy_game(game);
		exit(0);
	}
	return (0);
}
