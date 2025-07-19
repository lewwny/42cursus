/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 00:00:00 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/18 14:26:29 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_minimap(t_game *game)
{
	game->minimap.size = MINIMAP_SIZE;
	game->minimap.cell_size = MINIMAP_CELL_SIZE;
	game->minimap.radius = MINIMAP_RADIUS;
	game->minimap.x = WIDTH - game->minimap.size - 20;
	game->minimap.y = 20;
}

static void	put_pixel_to_buf(t_game *game, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		game->buf[y * WIDTH + x] = color;
}

static void	draw_filled_cell(t_game *game, int screen_x, int screen_y,
	int color)
{
	int	pixel_x;
	int	pixel_y;

	pixel_y = 0;
	while (pixel_y < game->minimap.cell_size)
	{
		pixel_x = 0;
		while (pixel_x < game->minimap.cell_size)
		{
			if (color != 0xffffff)
				put_pixel_to_buf(game, screen_x + pixel_x,
					screen_y + pixel_y, color);
			pixel_x++;
		}
		pixel_y++;
	}
}

void	draw_minimap_cell(t_game *game, int map_x, int map_y, int color)
{
	int	screen_x;
	int	screen_y;

	screen_x = game->minimap.x + map_x * game->minimap.cell_size;
	screen_y = game->minimap.y + map_y * game->minimap.cell_size;
	draw_filled_cell(game, screen_x, screen_y, color);
}
