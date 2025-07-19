/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fc_row.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:23:59 by macauchy          #+#    #+#             */
/*   Updated: 2025/07/14 13:58:29 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	calculate_skip_step(int range[2])
{
	if ((range[1] - range[0]) > HEIGHT * PIXEL_SKIP_THRESHOLD)
		return (2);
	return (1);
}

static int	should_skip_pixel(t_game *game, int y)
{
	if (abs(y - (HEIGHT / 2 + game->player.pitch)) < 2)
		return (1);
	if (y >= game->current_wall_start && y < game->current_wall_end)
		return (1);
	return (0);
}

static void	draw_px(t_game *game, int xy[2], int is_floor, double raydir[2])
{
	game->buf[xy[1] * WIDTH + xy[0]] = get_fc_c_p(game, xy,
			is_floor, raydir);
}

static void	fill_skipped_pixel(t_game *game, int x, int y, int skip_step)
{
	if (skip_step > 1 && y < HEIGHT)
		game->buf[(y - 1) * WIDTH + x] = game->buf[(y - skip_step) * WIDTH + x];
}

void	draw_fc_row(t_game *game, int params[2], int range[2], double raydir[2])
{
	int	y;
	int	x;
	int	is_floor;
	int	skip_step;

	x = params[0];
	is_floor = params[1];
	if (range[0] < 0)
		y = 0;
	else
		y = range[0];
	skip_step = calculate_skip_step(range);
	while (y < range[1] && y < HEIGHT)
	{
		if (should_skip_pixel(game, y))
		{
			y += skip_step;
			continue ;
		}
		draw_px(game, (int [2]){x, y}, is_floor, raydir);
		y += skip_step;
		fill_skipped_pixel(game, x, y, skip_step);
	}
}
