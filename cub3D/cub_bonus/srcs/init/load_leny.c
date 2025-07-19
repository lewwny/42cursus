/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_leny.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:53:17 by macauchy          #+#    #+#             */
/*   Updated: 2025/07/18 18:23:40 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	load_leny_idle(t_game *game)
{
	game->leny.leny_idle.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			"img/leny_idle.xpm", &game->leny.leny_idle.width,
			&game->leny.leny_idle.height);
	if (!game->leny.leny_idle.img_ptr)
		destroy_game_failure(game, "Failed to load leny idle image");
	game->leny.leny_idle.data = (unsigned int *)mlx_get_data_addr(
			game->leny.leny_idle.img_ptr, &game->leny.leny_idle.bpp,
			&game->leny.leny_idle.size_line, &game->leny.leny_idle.endian);
	if (!game->leny.leny_idle.data)
		destroy_game_failure(game, "Failed to get data address for leny idle");
}

static void	load_leny_shoot(t_game *game)
{
	game->leny.leny_shoot.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			"img/leny_shoot.xpm", &game->leny.leny_shoot.width,
			&game->leny.leny_shoot.height);
	if (!game->leny.leny_shoot.img_ptr)
		destroy_game_failure(game, "Failed to load leny shoot image");
	game->leny.leny_shoot.data = (unsigned int *)mlx_get_data_addr(
			game->leny.leny_shoot.img_ptr, &game->leny.leny_shoot.bpp,
			&game->leny.leny_shoot.size_line, &game->leny.leny_shoot.endian);
	if (!game->leny.leny_shoot.data)
		destroy_game_failure(game, "Failed to get data address for leny shoot");
}

static void	load_leny_shot(t_game *game)
{
	game->leny.leny_shot.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			"img/leny_shot.xpm", &game->leny.leny_shot.width,
			&game->leny.leny_shot.height);
	if (!game->leny.leny_shot.img_ptr)
		destroy_game_failure(game, "Failed to load leny shot image");
	game->leny.leny_shot.data = (unsigned int *)mlx_get_data_addr(
			game->leny.leny_shot.img_ptr, &game->leny.leny_shot.bpp,
			&game->leny.leny_shot.size_line, &game->leny.leny_shot.endian);
	if (!game->leny.leny_shot.data)
		destroy_game_failure(game, "Failed to get data address for leny shot");
}

void	load_leny(t_game *game)
{
	load_leny_idle(game);
	load_leny_shoot(game);
	load_leny_shot(game);
}
