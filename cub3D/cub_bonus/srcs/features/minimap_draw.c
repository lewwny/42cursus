/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 00:00:00 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/18 12:17:30 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	put_pixel_to_buf(t_game *game, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		game->buf[y * WIDTH + x] = color;
}

static void	draw_player_circle(t_game *game, int center_x, int center_y)
{
	int		x;
	int		y;
	double	dx;
	double	dy;

	y = center_y - 3;
	while (y <= center_y + 3)
	{
		x = center_x - 3;
		while (x <= center_x + 3)
		{
			dx = x - center_x;
			dy = y - center_y;
			if (sqrt(dx * dx + dy * dy) <= 3)
				put_pixel_to_buf(game, x, y, 0xFF0000);
			x++;
		}
		y++;
	}
}

static void	draw_player_direction(t_game *game, int center_x, int center_y)
{
	int	dir_x;
	int	dir_y;
	int	i;

	dir_x = center_x + (int)(game->player.dirx * 8);
	dir_y = center_y + (int)(game->player.diry * 8);
	i = 0;
	while (i <= 8)
	{
		put_pixel_to_buf(game, center_x + (int)((double)i / 8
				* (dir_x - center_x)), center_y + (int)((double)i / 8
				* (dir_y - center_y)), 0xFFFF00);
		i++;
	}
}

void	draw_minimap_player(t_game *game)
{
	int	center_x;
	int	center_y;

	center_x = game->minimap.x + game->minimap.size / 2;
	center_y = game->minimap.y + game->minimap.size / 2;
	draw_player_circle(game, center_x, center_y);
	draw_player_direction(game, center_x, center_y);
}
