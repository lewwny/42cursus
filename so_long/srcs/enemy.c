/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:03:38 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/05/12 11:58:49 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	find_enemy(char **map, int *y, int *x)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'M')
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

int	check_enemy(char **map)
{
	int	count;
	int	x;
	int	y;

	count = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map [y][x++] == 'M')
				count++;
		}
		y++;
	}
	return (count);
}

void	loose_game(t_game *game)
{
	ft_printf("Tu as perdu, piqué par le hérisson !\n");
	destroy_game(game);
}

static void	look_player(t_game *game, int new_y, int enemy_x)
{
	if (game->map[new_y][enemy_x] == 'P')
		loose_game(game);
}

void	move_enemy(t_game *game, int *direction)
{
	int	enemy_x;
	int	enemy_y;
	int	new_y;
	int	next_y;

	find_enemy(game->map, &enemy_y, &enemy_x);
	if (!*direction)
		next_y = 1;
	else
		next_y = -1;
	new_y = enemy_y + next_y;
	if (game->map[new_y][enemy_x] == '1' || game->map[new_y][enemy_x] == 'E'
			|| game->map[new_y][enemy_x] == 'C')
	{
		if (!*direction)
			*direction = 1;
		else
			*direction = 0;
		return ;
	}
	game->map[enemy_y][enemy_x] = '0';
	look_player(game, new_y, enemy_x);
	game->map[new_y][enemy_x] = 'M';
	render_map(game);
}
