/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:28:31 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/18 17:53:02 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_lifebar(t_game *game, int start_x, int start_y)
{
	int	lifebar;
	int	x;
	int	y;
	int	pixel;

	lifebar = _other()->lifebar_state;
	y = 0;
	while (y < 91)
	{
		x = 0;
		while (x < 400)
		{
			pixel = game->buf_lifebar[lifebar][y * 400 + x];
			if (pixel != 0xff00ff)
				game->buf[(start_y + y) * WIDTH + (start_x + x)] = pixel;
			x++;
		}
		y++;
	}
}

void	draw_crosshair(t_game *game, int start_x, int start_y, int shoot)
{
	int	x;
	int	y;
	int	pixel;

	y = 0;
	while (y < 13)
	{
		x = 0;
		while (x < 13)
		{
			if (shoot)
				pixel = game->bufcrosshair2[y * 13 + x];
			else
				pixel = game->bufcrosshair1[y * 13 + x];
			if (pixel != 0xff00ff)
				game->buf[(start_y + y) * WIDTH + (start_x + x)] = pixel;
			x++;
		}
		y++;
	}
}

void	draw_button(t_game *game, int start_x, int start_y, int *buf)
{
	int	x;
	int	y;
	int	pixel;

	y = 0;
	while (y < 300)
	{
		x = 0;
		while (x < 300)
		{
			pixel = buf[y * 300 + x];
			if (pixel != 0xff00ff)
				game->buf[(start_y + y) * WIDTH + (start_x + x)] = pixel;
			x++;
		}
		y++;
	}
}

void	draw_waiting_screen(t_game *game)
{
	int	x;
	int	y;
	int	pixel;

	y = 0;
	while (y < 233)
	{
		x = 0;
		while (x < 350)
		{
			pixel = game->wait_buf[y * 350 + x];
			if (pixel != 0xff00ff)
				game->buf[y * WIDTH + x] = pixel;
			x++;
		}
		y++;
	}
}

void	handle_crosshair_animation(t_game *game)
{
	if (game->menu_mode != 4)
		return ;
	if (game->crosshair)
	{
		game->crosshair_timer += game->delta_time;
		if (game->crosshair_timer > 0.1)
		{
			game->crosshair = 0;
			game->crosshair_timer = 0;
		}
	}
}
