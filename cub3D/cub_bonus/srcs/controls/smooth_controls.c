/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smooth_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:30:00 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/16 12:49:42 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	handle_movement(t_game *game)
{
	if (game->menu_mode != 4)
		return ;
	if (game->keys.w)
		move_player(game, KEY_W);
	if (game->keys.s)
		move_player(game, KEY_S);
	if (game->keys.a)
		move_player(game, KEY_A);
	if (game->keys.d)
		move_player(game, KEY_D);
}

void	handle_vertical_rotation(t_game *game)
{
	double	vertical_speed;

	vertical_speed = 1000.0 * game->delta_time;
	if (vertical_speed > 30.0)
		vertical_speed = 30.0;
	if (game->keys.up && game->player.pitch < 400)
		game->player.pitch += vertical_speed;
	if (game->keys.down && game->player.pitch > -400)
		game->player.pitch -= vertical_speed;
}

void	rotate_left(t_game *game, double rotation_speed)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = game->player.dirx;
	old_planex = game->player.planex;
	game->player.dirx = game->player.dirx * cos(-rotation_speed)
		- game->player.diry * sin(-rotation_speed);
	game->player.diry = old_dirx * sin(-rotation_speed)
		+ game->player.diry * cos(-rotation_speed);
	game->player.planex = game->player.planex * cos(-rotation_speed)
		- game->player.planey * sin(-rotation_speed);
	game->player.planey = old_planex * sin(-rotation_speed)
		+ game->player.planey * cos(-rotation_speed);
}

void	rotate_right(t_game *game, double rotation_speed)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = game->player.dirx;
	old_planex = game->player.planex;
	game->player.dirx = game->player.dirx * cos(rotation_speed)
		- game->player.diry * sin(rotation_speed);
	game->player.diry = old_dirx * sin(rotation_speed)
		+ game->player.diry * cos(rotation_speed);
	game->player.planex = game->player.planex * cos(rotation_speed)
		- game->player.planey * sin(rotation_speed);
	game->player.planey = old_planex * sin(rotation_speed)
		+ game->player.planey * cos(rotation_speed);
}

void	handle_rotation(t_game *game)
{
	double	base_rotation_speed;
	double	frame_rotation_speed;

	if (game->menu_mode != 4)
		return ;
	base_rotation_speed = 2.0;
	frame_rotation_speed = base_rotation_speed * game->delta_time;
	if (frame_rotation_speed > 0.1)
		frame_rotation_speed = 0.1;
	if (game->keys.left)
		rotate_left(game, frame_rotation_speed);
	if (game->keys.right)
		rotate_right(game, frame_rotation_speed);
	handle_vertical_rotation(game);
}
