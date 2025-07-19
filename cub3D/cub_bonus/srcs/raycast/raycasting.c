/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:54:43 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/18 18:39:59 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	cast_ray(t_game *game, double raydirx, double raydiry)
{
	t_ray	*ray;

	ray = &game->player.ray;
	ray->ray_x = game->player.posx;
	ray->ray_y = game->player.posy;
	ray->mapx = (int)ray->ray_x;
	ray->mapy = (int)ray->ray_y;
	init_sides(game, raydirx, raydiry);
	game->player.ray.hit = false;
	perform_dda(game);
}

void	calculate_ray_dir(t_game *game, int x, double *raydirx, double *raydiry)
{
	double			camera_x;
	double			ray_angle;
	static double	fov_half;
	static double	width_inv;

	fov_half = game->player.fov / 2.0;
	width_inv = 1.0 / WIDTH;
	camera_x = (2 * x * width_inv) - 1;
	ray_angle = atan2(game->player.diry, game->player.dirx)
		+ camera_x * fov_half;
	*raydirx = cos(ray_angle);
	*raydiry = sin(ray_angle);
}

static void	process_ray(t_game *game, double raydirx, double raydiry, int x)
{
	cast_ray(game, raydirx, raydiry);
	game->player.ray.distance *= (raydirx * game->player.dirx)
		+ (raydiry * game->player.diry);
	wall_height(game);
	set_texture(game, raydirx, raydiry);
	if (game->player.ray.wall.start > 0)
		game->current_wall_start = game->player.ray.wall.start;
	else
		game->current_wall_start = 0;
	if (game->player.ray.wall.end < HEIGHT)
		game->current_wall_end = game->player.ray.wall.end;
	else
		game->current_wall_end = HEIGHT - 1;
	draw_wall(game, x);
	draw_fc_col(game, x, raydirx, raydiry);
	game->z_buffer[x] = game->player.ray.distance;
}

void	raycasting(t_game *game)
{
	int		x;
	double	raydirx;
	double	raydiry;

	x = 0;
	while (x++ < WIDTH)
	{
		calculate_ray_dir(game, x, &raydirx, &raydiry);
		process_ray(game, raydirx, raydiry, x);
	}
	draw_leny_at_other_position(game);
	pthread_mutex_lock(&game->server.mutex);
	if (game->host && !_other()->connected)
		draw_waiting_screen(game);
	if ((game->host && _other()->connected) || game->join)
	{
		draw_gun(game, 680, 300, game->shoot);
		draw_lifebar(game, 0, 0);
		draw_crosshair(game, 634, 354, game->crosshair);
	}
	draw_minimap(game);
	pthread_mutex_unlock(&game->server.mutex);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->buftmp, 0, 0);
}
