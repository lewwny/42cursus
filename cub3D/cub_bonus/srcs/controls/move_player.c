/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:04:31 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/16 12:45:47 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	move_player_forward(t_game *game, double move_speed)
{
	double	new_y;
	double	new_x;

	new_y = game->player.posy + game->player.diry * move_speed;
	new_x = game->player.posx + game->player.dirx * move_speed;
	if (can_move_axis(game, game->player.posx, new_y, COL_BUF))
		game->player.posy = new_y;
	if (can_move_axis(game, new_x, game->player.posy, COL_BUF))
		game->player.posx = new_x;
}

static void	move_player_backward(t_game *game, double move_speed)
{
	double	new_y;
	double	new_x;

	new_y = game->player.posy - game->player.diry * move_speed;
	new_x = game->player.posx - game->player.dirx * move_speed;
	if (can_move_axis(game, game->player.posx, new_y, COL_BUF))
		game->player.posy = new_y;
	if (can_move_axis(game, new_x, game->player.posy, COL_BUF))
		game->player.posx = new_x;
}

static void	move_player_right(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.posx - game->player.diry * move_speed;
	new_y = game->player.posy + game->player.dirx * move_speed;
	if (can_move_axis(game, new_x, game->player.posy, COL_BUF))
		game->player.posx = new_x;
	if (can_move_axis(game, game->player.posx, new_y, COL_BUF))
		game->player.posy = new_y;
}

static void	move_player_left(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.posx + game->player.diry * move_speed;
	new_y = game->player.posy - game->player.dirx * move_speed;
	if (can_move_axis(game, new_x, game->player.posy, COL_BUF))
		game->player.posx = new_x;
	if (can_move_axis(game, game->player.posx, new_y, COL_BUF))
		game->player.posy = new_y;
}

void	move_player(t_game *game, int keycode)
{
	double	base_speed;
	double	frame_speed;
	double	sprint_multiplier;

	base_speed = 3.0;
	sprint_multiplier = 1.0;
	if (game->keys.shift && (game->keys.w || game->keys.s))
		sprint_multiplier = 1.5;
	frame_speed = base_speed * sprint_multiplier * game->delta_time;
	if (frame_speed > 0.15)
		frame_speed = 0.15;
	if (keycode == KEY_W)
		move_player_forward(game, frame_speed);
	else if (keycode == KEY_S)
		move_player_backward(game, frame_speed);
	else if (keycode == KEY_A)
		move_player_left(game, frame_speed);
	else if (keycode == KEY_D)
		move_player_right(game, frame_speed);
}
