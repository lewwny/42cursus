/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:56:34 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/14 13:20:36 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	rotate_vector(double *x, double *y, double cos_angle, double sin_a)
{
	double	old_x;

	old_x = *x;
	*x = *x * cos_angle - *y * sin_a;
	*y = old_x * sin_a + *y * cos_angle;
}

static void	turn_player(t_game *game, int direction)
{
	double	rotation_speed;
	double	angle;
	double	cos_angle;
	double	sin_angle;

	rotation_speed = 0.015;
	if (direction == -1)
		angle = -rotation_speed;
	else if (direction == 1)
		angle = rotation_speed;
	else
		return ;
	cos_angle = cos(angle);
	sin_angle = sin(angle);
	rotate_vector(&game->player.dirx,
		&game->player.diry, cos_angle, sin_angle);
	rotate_vector(&game->player.planex,
		&game->player.planey, cos_angle, sin_angle);
}

int	key_hook(int keycode, t_game *game)
{
	if ((keycode == KEY_W || keycode == KEY_A || keycode == KEY_S
			|| keycode == KEY_D) && game->menu_mode == 4)
		move_player(game, keycode);
	if (keycode == KEY_LEFT && game->menu_mode == 4)
		turn_player(game, -1);
	if (keycode == KEY_RIGHT && game->menu_mode == 4)
		turn_player(game, 1);
	return (0);
}
