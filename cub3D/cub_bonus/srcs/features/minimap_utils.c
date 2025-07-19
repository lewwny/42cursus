/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 00:00:00 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/18 14:27:00 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_valid_position(t_game *game, int map_x, int map_y)
{
	if (map_y >= 0 && map_y < (int)ft_strarrlen(game->final_map)
		&& map_x >= 0 && map_x < (int)ft_strlen(game->final_map[map_y]))
		return (1);
	return (0);
}

static int	is_walkable_cell(char cell)
{
	if (cell == '0' || cell == 'N' || cell == 'S'
		|| cell == 'E' || cell == 'W')
		return (1);
	return (0);
}

int	get_cell_color(t_game *game, int map_x, int map_y)
{
	if (is_valid_position(game, map_x, map_y))
	{
		if (game->final_map[map_y][map_x] == '1')
			return (0x000000);
		else if (is_walkable_cell(game->final_map[map_y][map_x]))
			return (0x808080);
		else
			return (0xffffff);
	}
	else
		return (0xffffff);
}

void	draw_minimap_cell_row(t_game *game, t_minimap_params *params)
{
	int	minimap_col;
	int	map_x;
	int	color;

	minimap_col = 0;
	map_x = params->start_map_x;
	while (map_x <= params->end_map_x)
	{
		color = get_cell_color(game, map_x, params->map_y);
		draw_minimap_cell(game, minimap_col, params->minimap_row, color);
		minimap_col++;
		map_x++;
	}
}

void	draw_minimap(t_game *game)
{
	int					player_map_x;
	int					player_map_y;
	t_minimap_params	params;

	player_map_x = (int)game->player.posx;
	player_map_y = (int)game->player.posy;
	params.start_map_x = player_map_x - game->minimap.radius;
	params.end_map_x = player_map_x + game->minimap.radius;
	params.minimap_row = 0;
	params.map_y = player_map_y - game->minimap.radius;
	while (params.map_y <= player_map_y + game->minimap.radius)
	{
		draw_minimap_cell_row(game, &params);
		params.minimap_row++;
		params.map_y++;
	}
	draw_minimap_player(game);
}
