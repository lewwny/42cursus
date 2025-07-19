/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:52:49 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/05/07 12:04:30 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static char	**copy_map(char **map)
{
	int		i;
	char	**new_map;

	i = 0;
	while (map[i])
		i++;
	new_map = malloc(sizeof(char *) * (i + 1));
	if (!new_map)
		malloc_error(map);
	i = 0;
	while (map[i])
	{
		new_map[i] = ft_strdup(map[i]);
		if (!new_map[i])
		{
			free_map(new_map);
			malloc_error(map);
		}
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}

static void	flood_fill(char **map, int x, int y)
{
	if (x < 0 || y < 0 || !map[y] || map[y][x] == '\0')
		return ;
	if (map[y][x] == '1' || map[y][x] == 'V' || map[y][x] == 'M')
		return ;
	map[y][x] = 'V';
	flood_fill(map, x - 1, y);
	flood_fill(map, x + 1, y);
	flood_fill(map, x, y - 1);
	flood_fill(map, x, y + 1);
}

static void	search_v(char **map_copy, char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map_copy[y])
	{
		x = 0;
		while (map_copy[y][x])
		{
			if (map_copy[y][x] == 'E' || map_copy[y][x] == 'C')
			{
				free_map(map_copy);
				invalid_map(map);
			}
			x++;
		}
		y++;
	}
}

void	test_path(char **map)
{
	char	**map_copy;
	int		x;
	int		y;

	map_copy = copy_map(map);
	y = 0;
	while (map_copy[y])
	{
		x = 0;
		while (map_copy[y][x])
		{
			if (map_copy[y][x] == 'P')
			{
				flood_fill(map_copy, x, y);
				break ;
			}
			x++;
		}
		y++;
	}
	search_v(map_copy, map);
	free_map(map_copy);
}
