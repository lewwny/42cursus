/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:51:02 by macauchy          #+#    #+#             */
/*   Updated: 2025/07/18 16:15:09 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static double	get_max_radius(void)
{
	if (PLAYER_HITBOX_WIDTH > PLAYER_HITBOX_HEIGHT)
		return (PLAYER_HITBOX_WIDTH);
	return (PLAYER_HITBOX_HEIGHT);
}

static double	get_projection_length(t_game *game, double dx, double dy)
{
	return (dx * game->player.dirx + dy * game->player.diry);
}

static void	get_closest_point(t_game *game, double proj_len,
		double *x, double *y)
{
	*x = game->player.posx + game->player.dirx * proj_len;
	*y = game->player.posy + game->player.diry * proj_len;
}

int	ray_hits_player(t_game *game, double target_x, double target_y)
{
	double	dx;
	double	dy;
	double	proj_len;
	double	closest_x;
	double	closest_y;

	dx = target_x - game->player.posx;
	dy = target_y - game->player.posy;
	if (sqrt(dx * dx + dy * dy) > 10.0 || sqrt(dx * dx + dy * dy) < 0.1)
		return (0);
	proj_len = get_projection_length(game, dx, dy);
	if (proj_len < 0)
		return (0);
	get_closest_point(game, proj_len, &closest_x, &closest_y);
	if (sqrt((target_x - closest_x) * (target_x - closest_x)
			+ (target_y - closest_y) * (target_y - closest_y))
		<= get_max_radius() / 2.0)
		return (1);
	return (0);
}
