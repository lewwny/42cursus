/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:00:05 by macauchy          #+#    #+#             */
/*   Updated: 2025/07/18 18:54:07 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	match_color_tex(t_game *game)
{
	int	side;
	int	index;

	side = game->player.ray.wall.side;
	if (side < 0 || side >= 6 || !game->texture.tex_ptr[side].data)
		return (0x654321);
	index = game->player.ray.wall.tex_y
		* game->texture.tex_ptr[side].width
		+ game->player.ray.wall.tex_x;
	if (index < 0 || index >= (game->texture.tex_ptr[side].width
			* game->texture.tex_ptr[side].height))
		return (0x654321);
	game->player.ray.wall.color = game->texture.tex_ptr[side].data[index];
	return (game->player.ray.wall.color);
}

void	calculate_y_tex(t_game *game)
{
	int	tex_height;
	int	side;

	side = game->player.ray.wall.side;
	if (side < 0 || side >= 6)
	{
		game->player.ray.wall.tex_y = 0;
		return ;
	}
	tex_height = game->texture.tex_ptr[side].height;
	game->player.ray.wall.tex_y = (int)game->player.ray.wall.tex_pos;
	if (game->player.ray.wall.tex_y < 0)
		game->player.ray.wall.tex_y = 0;
	else if (game->player.ray.wall.tex_y >= tex_height)
		game->player.ray.wall.tex_y = tex_height - 1;
}

void	draw_wall_textured(t_game *game, int x, int y)
{
	unsigned int	color;
	int				side;

	calculate_y_tex(game);
	side = game->player.ray.wall.side;
	if (side < 0 || side >= 6 || !game->texture.tex_ptr[side].data)
	{
		game->buf[y * WIDTH + x] = 0x654321;
		game->player.ray.wall.tex_pos += game->player.ray.wall.step;
		return ;
	}
	if (game->player.ray.wall.tex_x >= 0
		&& game->player.ray.wall.tex_x < game->texture.tex_ptr[side].width
		&& game->player.ray.wall.tex_y >= 0
		&& game->player.ray.wall.tex_y < game->texture.tex_ptr[side].height)
	{
		color = match_color_tex(game);
		color = apply_shading(color, game->player.ray.distance);
		game->buf[y * WIDTH + x] = color;
	}
	else
		game->buf[y * WIDTH + x] = 0x654321;
	game->player.ray.wall.tex_pos += game->player.ray.wall.step;
}
