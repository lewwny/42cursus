/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:22:16 by macauchy          #+#    #+#             */
/*   Updated: 2025/07/14 13:58:29 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	perform_dda_step(t_game *game)
{
	if (game->player.ray.side_dist_x < game->player.ray.side_dist_y)
	{
		game->player.ray.side = NO_SO;
		game->player.ray.mapx += game->player.ray.step_size_x;
		game->player.ray.distance = game->player.ray.side_dist_x;
		game->player.ray.side_dist_x += game->player.ray.delta_dist_x;
	}
	else
	{
		game->player.ray.side = WE_EA;
		game->player.ray.mapy += game->player.ray.step_size_y;
		game->player.ray.distance = game->player.ray.side_dist_y;
		game->player.ray.side_dist_y += game->player.ray.delta_dist_y;
	}
}

static bool	check_hit(t_game *game)
{
	if (game->player.ray.mapx < 0 || game->player.ray.mapx >= game->width
		|| game->player.ray.mapy < 0 || game->player.ray.mapy >= game->height)
	{
		return (true);
	}
	else if (game->final_map[game->player.ray.mapy]
		[game->player.ray.mapx] == '1')
	{
		return (true);
	}
	return (false);
}

void	perform_dda(t_game *game)
{
	while (!game->player.ray.hit)
	{
		perform_dda_step(game);
		if (check_hit(game))
			game->player.ray.hit = true;
	}
	set_sides(game);
}
