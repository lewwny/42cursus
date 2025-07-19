/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_texture2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:24:30 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/15 08:54:58 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	extract_floor(t_game *game)
{
	game->texture.floor = mlx_xpm_file_to_image(game->mlx_ptr, "img/ceil.xpm",
			&game->texture.tex_ptr[FLOOR].width,
			&game->texture.tex_ptr[FLOOR].height);
	if (!game->texture.floor)
		destroy_game_failure(game, "Failed to load FLOOR texture");
	game->texture.tex_ptr[FLOOR].data = (unsigned int *)mlx_get_data_addr(
			game->texture.floor, &game->texture.tex_ptr[FLOOR].bpp,
			&game->texture.tex_ptr[FLOOR].size_line,
			&game->texture.tex_ptr[FLOOR].endian);
	game->texture.floor_data = game->texture.tex_ptr[FLOOR].data;
}

void	extract_ceiling(t_game *game)
{
	game->texture.ceiling = mlx_xpm_file_to_image(game->mlx_ptr,
			"img/floor.xpm",
			&game->texture.tex_ptr[CEILING].width,
			&game->texture.tex_ptr[CEILING].height);
	if (!game->texture.ceiling)
		destroy_game_failure(game, "Failed to load CEILING texture");
	game->texture.tex_ptr[CEILING].data = (unsigned int *)mlx_get_data_addr(
			game->texture.ceiling, &game->texture.tex_ptr[CEILING].bpp,
			&game->texture.tex_ptr[CEILING].size_line,
			&game->texture.tex_ptr[CEILING].endian);
	game->texture.ceiling_data = game->texture.tex_ptr[CEILING].data;
}
