/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:26:02 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/18 18:50:37 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_gun(t_game *game, int start_x, int start_y, int shoot)
{
	int	x;
	int	y;
	int	pixel;

	y = 0;
	while (y < 525)
	{
		x = 0;
		while (x < 350)
		{
			if (shoot)
				pixel = game->bufgun2[y * 350 + x];
			else
				pixel = game->bufgun[y * 350 + x];
			if (pixel != 0xff00ff)
				game->buf[(start_y + y) * WIDTH + (start_x + x)] = pixel;
			x++;
		}
		y++;
	}
}

void	handle_shoot_animation(t_game *game)
{
	if (game->menu_mode != 4)
		return ;
	if (game->shoot)
	{
		game->shoot_timer += game->delta_time;
		if (game->shoot_timer > 0.1)
		{
			game->shoot = 0;
			game->shoot_timer = 0;
		}
	}
}

static int	shot_blocked_by_wall(t_game *game, double target_x, double target_y)
{
	double	distance_to_target;
	double	raydirx;
	double	raydiry;
	t_ray	original_ray;
	int		blocked;

	raydirx = target_x - game->player.posx;
	raydiry = target_y - game->player.posy;
	distance_to_target = sqrt(raydirx * raydirx + raydiry * raydiry);
	raydirx /= distance_to_target;
	raydiry /= distance_to_target;
	original_ray = game->player.ray;
	cast_ray(game, raydirx, raydiry);
	blocked = (game->player.ray.distance < distance_to_target - 0.1);
	game->player.ray = original_ray;
	return (blocked);
}

static int	check_shot_hit(t_game *game)
{
	double	target_x;
	double	target_y;

	target_x = _other()->otherposx;
	target_y = _other()->otherposy;
	if (target_x < 0.1 && target_y < 0.1)
		return (0);
	if (!ray_hits_player(game, target_x, target_y))
		return (0);
	if (shot_blocked_by_wall(game, target_x, target_y))
		return (0);
	return (1);
}

void	is_shot(t_game *game)
{
	ssize_t	write_result;

	if (!game->shoot)
		return ;
	if (!check_shot_hit(game))
		return ;
	game->crosshair = 1;
	pthread_mutex_lock(&game->server.mutex);
	if (game->host && _other()->connected && (!_other()->end2
			|| !_other()->end))
	{
		write_result = write(game->server.client_fd, "shot", 4);
		if (write_result < 0)
		{
			_other()->connected = 0;
			_other()->end2 = 1;
		}
	}
	else if (game->join && (_other()->end || _other()->end2))
	{
		write_result = write(game->sock, "shot", 4);
		if (write_result < 0)
			_other()->end = 1;
	}
	pthread_mutex_unlock(&game->server.mutex);
}
