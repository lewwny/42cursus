/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:17:00 by macauchy          #+#    #+#             */
/*   Updated: 2025/07/14 13:41:47 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	wall_height(t_game *game)
{
	t_ray	*ray;

	ray = &game->player.ray;
	ray->wall.height = (int)(HEIGHT / ray->distance);
	ray->wall.start = -ray->wall.height / 2 + HEIGHT / 2 + game->player.pitch;
	if (ray->wall.start < 0)
		ray->wall.start = 0;
	ray->wall.end = ray->wall.height / 2 + HEIGHT / 2 + game->player.pitch;
	if (ray->wall.end >= HEIGHT)
		ray->wall.end = HEIGHT;
}

void	draw_wall(t_game *game, int x)
{
	t_ray	*ray;
	int		y;

	ray = &game->player.ray;
	y = 0;
	while (y < HEIGHT)
	{
		if (y >= ray->wall.start && y < ray->wall.end)
			draw_wall_textured(game, x, y);
		y++;
	}
}
