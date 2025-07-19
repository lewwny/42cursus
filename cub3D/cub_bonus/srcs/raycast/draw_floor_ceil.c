/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_ceil.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:06:28 by macauchy          #+#    #+#             */
/*   Updated: 2025/07/14 17:24:10 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_optimization_cache(t_game *game)
{
	int		i;
	double	camera_x;
	double	dy;

	if (game->cache_initialized)
		return ;
	i = 0;
	while (i < WIDTH)
	{
		camera_x = (2.0 * i / (double)WIDTH) - 1.0;
		game->cached_cos_values[i] = cos(camera_x * (game->player.fov / 2.0));
		i++;
	}
	i = 0;
	while (i < HEIGHT)
	{
		dy = i - (HEIGHT / 2.0);
		if (fabs(dy) > 0.1)
			game->cached_inv_values[i] = (HEIGHT / 2.0) / fabs(dy);
		else
			game->cached_inv_values[i] = 0.0;
		i++;
	}
	game->cache_initialized = 1;
}

static void	update_floor_coords_p(t_game *game, int xy[2], double raydir[2])
{
	double	distance_factor;
	double	dy_adjusted;

	dy_adjusted = xy[1] - (HEIGHT / 2.0 + game->player.pitch);
	if (fabs(dy_adjusted) < 0.1)
	{
		game->player.ray.floor.floor_x = game->player.posx;
		game->player.ray.floor.floor_y = game->player.posy;
		return ;
	}
	distance_factor = (HEIGHT / 2.0) / fabs(dy_adjusted)
		/ game->cached_cos_values[xy[0]];
	game->player.ray.floor.floor_x = game->player.posx + raydir[0]
		* distance_factor;
	game->player.ray.floor.floor_y = game->player.posy + raydir[1]
		* distance_factor;
}

unsigned int	get_fc_c_p(t_game *game, int xy[2], int is_f, double raydir[2])
{
	unsigned int	color;
	int				tex_index;
	double			dx;
	double			dy;
	double			distance;

	init_optimization_cache(game);
	update_floor_coords_p(game, xy, raydir);
	if (is_f)
		tex_index = CEILING;
	else
		tex_index = FLOOR;
	color = get_fc_text_color(game, tex_index);
	dx = game->player.ray.floor.floor_x - game->player.posx;
	dy = game->player.ray.floor.floor_y - game->player.posy;
	distance = sqrt(dx * dx + dy * dy);
	return (apply_shading(color, distance));
}

void	draw_fc_col(t_game *game, int x, double raydirx, double raydiry)
{
	int	wall_start;
	int	wall_end;

	if (game->player.ray.wall.start < 0)
		wall_start = 0;
	else
		wall_start = game->player.ray.wall.start;
	if (game->player.ray.wall.end >= HEIGHT)
		wall_end = HEIGHT - 1;
	else
		wall_end = game->player.ray.wall.end;
	if (x < 0 || x >= WIDTH)
		return ;
	draw_fc_row(game, (int [2]){x, 0}, (int [2]){0, wall_start},
		(double [2]){raydirx, raydiry});
	draw_fc_row(game, (int [2]){x, 1}, (int [2]){wall_end, HEIGHT},
		(double [2]){raydirx, raydiry});
}
