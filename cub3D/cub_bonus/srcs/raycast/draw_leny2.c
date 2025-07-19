/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_leny2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:33:11 by macauchy          #+#    #+#             */
/*   Updated: 2025/07/18 18:33:42 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	put_pixel_safe(t_game *game, int x, int y, unsigned int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT
		&& color != 0xFF00FF && color != 0x00FF00FF)
		game->buf[y * WIDTH + x] = color;
}

int	is_pixel_visible(t_game *game, int screen_x, double sprite_distance)
{
	double	wall_distance;

	if (screen_x < 0 || screen_x >= WIDTH)
		return (0);
	wall_distance = game->z_buffer[screen_x];
	return (sprite_distance < wall_distance - 0.05);
}

void	draw_sprite_pixel_row(t_game *game, t_sprite_draw *draw,
		t_img *sprite, int y)
{
	int				x;
	int				pixel_x;
	int				pixel_y;
	unsigned int	color;

	x = 0;
	while (x++ < draw->size)
	{
		pixel_x = draw->screen_x - draw->size / 2 + x;
		pixel_y = draw->screen_y + y;
		if (pixel_x >= 0 && pixel_x < WIDTH
			&& pixel_y >= 0 && pixel_y < HEIGHT
			&& is_pixel_visible(game, pixel_x, draw->sprite_distance))
		{
			if ((x * sprite->width) / draw->size >= 0
				&& (x * sprite->width) / draw->size < sprite->width
				&& (y * sprite->height) / draw->size >= 0
				&& (y * sprite->height) / draw->size < sprite->height)
			{
				color = sprite->data[(y * sprite->height) / draw->size
					* sprite->width + (x * sprite->width) / draw->size];
				put_pixel_safe(game, pixel_x, pixel_y, color);
			}
		}
	}
}

void	draw_sprite_pixel(t_game *game, t_sprite_draw *draw, t_img *sprite)
{
	int	y;

	y = 0;
	while (y < draw->size)
	{
		draw_sprite_pixel_row(game, draw, sprite, y);
		y++;
	}
}
