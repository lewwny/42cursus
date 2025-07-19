/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_leny.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:17:49 by macauchy          #+#    #+#             */
/*   Updated: 2025/07/18 18:33:27 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	draw_fallback_square(t_game *game, t_sprite_draw *draw)
{
	int	x;
	int	y;
	int	pixel_x;
	int	pixel_y;

	y = 0;
	while (y < draw->size)
	{
		x = 0;
		while (x < draw->size)
		{
			pixel_x = draw->screen_x - draw->size / 2 + x;
			pixel_y = draw->screen_y + y;
			if (pixel_x >= 0 && pixel_x < WIDTH
				&& pixel_y >= 0 && pixel_y < HEIGHT
				&& is_pixel_visible(game, pixel_x, draw->sprite_distance))
			{
				game->buf[pixel_y * WIDTH + pixel_x] = 0x00FF00;
			}
			x++;
		}
		y++;
	}
}

static void	draw_leny_sprite(t_game *game, t_sprite_draw *draw)
{
	t_img	*sprite;

	sprite = &game->leny.leny_idle;
	if (!sprite || !sprite->data)
	{
		draw_fallback_square(game, draw);
		return ;
	}
	draw_sprite_pixel(game, draw, sprite);
}

static int	calculate_sprite_ground_y(t_game *game, double sprite_distance)
{
	double	horizon_y;
	double	perspective_offset;
	double	ground_y;

	horizon_y = HEIGHT / 2.0 + game->player.pitch;
	perspective_offset = (HEIGHT / 4.0) / (sprite_distance + 0.5);
	ground_y = horizon_y + perspective_offset;
	return ((int)ground_y);
}

static int	calculate_sprite_size(double distance)
{
	int	sprite_size;

	sprite_size = (int)(HEIGHT * 0.8 / distance);
	if (sprite_size < 1)
		sprite_size = 1;
	return (sprite_size);
}

void	draw_leny_at_other_position(t_game *game)
{
	int				screen_x;
	double			distance;
	double			enemy_x;
	double			enemy_y;
	t_sprite_draw	draw;

	if (!game->host && !game->join)
		return ;
	enemy_x = _other()->otherposx;
	enemy_y = _other()->otherposy;
	if (enemy_x == 0.0 && enemy_y == 0.0)
		return ;
	if (!world_to_screen_simple(game, enemy_x, enemy_y, &screen_x))
		return ;
	distance = sqrt(pow(enemy_x - game->player.posx, 2)
			+ pow(enemy_y - game->player.posy, 2));
	draw.size = calculate_sprite_size(distance);
	draw.screen_x = screen_x;
	draw.screen_y = calculate_sprite_ground_y(game, distance) - draw.size;
	draw.sprite_distance = distance;
	draw_leny_sprite(game, &draw);
}
