/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:57:01 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/05/07 11:41:20 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	check_collectible(char **map)
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
			if (map [y][x++] == 'C')
				count++;
		}
		y++;
	}
	return (count);
}

static int	check_exit(char **map)
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
			if (map [y][x++] == 'E')
				count++;
		}
		y++;
	}
	if (count == 1)
		return (1);
	return (0);
}

static int	check_player(char **map)
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
			if (map [y][x++] == 'P')
				count++;
		}
		y++;
	}
	if (count == 1)
		return (1);
	return (0);
}

static int	check_char(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map [y][x] != 'P' && map [y][x] != '0' &&
				map [y][x] != 'E' && map [y][x] != '1' &&
				map [y][x] != 'C' && map [y][x] != '\n' &&
				map[y][x] != 'M')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

void	parse_map_char(t_game *game)
{
	game->collectible_left = check_collectible(game->map);
	if (!game->collectible_left)
		invalid_map(game->map);
	if (!check_exit(game->map))
		invalid_map(game->map);
	if (!check_player(game->map))
		invalid_map(game->map);
	if (!check_char(game->map))
		invalid_map(game->map);
	game->enemy = check_enemy(game->map);
	if (game->enemy > 1)
		invalid_map(game->map);
}
