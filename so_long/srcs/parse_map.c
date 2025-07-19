/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:36:45 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/05/06 17:14:17 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	parse_form(char **map)
{
	int	size_x;
	int	i;

	i = 0;
	size_x = ft_strlen(map[i]);
	while (map[i])
	{
		if (map[i][size_x - 1] != '\n')
			return (0);
		i++;
	}
	return (1);
}

static int	parse_wall(char **map)
{
	int	size_x;
	int	size_y;
	int	i;

	i = 0;
	size_y = 0;
	size_x = ft_strlen(map[0]) - 1;
	while (map[size_y])
		size_y++;
	while (i < size_x - 1)
	{
		if (map[0][i] != '1' || map[size_y - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < size_y - 1)
	{
		if (map[i][0] != '1' || map[i][size_x - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

void	parse_map(t_game *game)
{
	parse_map_char(game);
	if (!parse_form(game->map))
		invalid_map(game->map);
	if (!parse_wall(game->map))
		invalid_map(game->map);
	test_path(game->map);
}
