/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   os.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <lenygarcia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:10:35 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/04 20:53:31 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#ifdef __linux__

void	free_linux(t_game *game)
{
	if (game->mlx_ptr)
		mlx_destroy_display(game->mlx_ptr);
}

void	mouse_move(t_game *game, int x, int y)
{
	mlx_mouse_move(game->mlx_ptr, game->win_ptr, x, y);
}

#endif

#ifdef __APPLE__

void	free_linux(t_game *game)
{
	(void)game;
}

void	mouse_move(t_game *game, int x, int y)
{
	(void)game;
	(void)x;
	(void)y;
}

#endif