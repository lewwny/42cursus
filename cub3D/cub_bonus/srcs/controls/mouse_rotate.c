/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:50:08 by macauchy          #+#    #+#             */
/*   Updated: 2025/07/14 13:30:42 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	rotate_player_horizontal(t_game *game, int delta_x)
{
	double	rot_speed;
	double	current_angle;
	double	new_angle;

	if (delta_x == 0)
		return (0);
	rot_speed = ROT_SPEED / 1.5;
	current_angle = atan2(game->player.diry, game->player.dirx);
	new_angle = current_angle + (delta_x * rot_speed);
	game->player.dirx = cos(new_angle);
	game->player.diry = sin(new_angle);
	game->player.planex = -sin(new_angle) * game->player.fov;
	game->player.planey = cos(new_angle) * game->player.fov;
	return (1);
}

static int	rotate_player_vertical(t_game *game, int delta_y)
{
	if (delta_y == 0)
		return (0);
	game->player.pitch -= delta_y;
	if (game->player.pitch > 400)
		game->player.pitch = 400;
	else if (game->player.pitch < -400)
		game->player.pitch = -400;
	return (1);
}

int	rotate_player_by_mouse(t_game *game, int delta_x, int delta_y)
{
	int	rotated;

	rotated = 0;
	rotated |= rotate_player_horizontal(game, delta_x);
	rotated |= rotate_player_vertical(game, delta_y);
	return (rotated);
}
