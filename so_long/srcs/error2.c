/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:57:05 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/05/13 07:45:20 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	error_mlx(t_game *game)
{
	free_map(game->map);
	ft_printf("Error\nMLX failed\n");
	exit(1);
}

void	error_load(t_game *game)
{
	ft_printf("Error\nImage load fail\n");
	destroy_error(game);
	exit(1);
}

void	malloc_error2(t_game *game)
{
	ft_printf("Error\nProblème d'allocation mémoire\n");
	destroy_error(game);
	exit(1);
}

static void	destroy_collectible(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->num_collectible_frame)
	{
		mlx_destroy_image(game->mlx, game->img_collectible[i]);
		i++;
	}
	free(game->img_collectible);
}

void	destroy_error(t_game *game)
{
	if (game->img_wall)
		mlx_destroy_image(game->mlx, game->img_wall);
	if (game->img_floor)
		mlx_destroy_image(game->mlx, game->img_floor);
	if (game->img_player)
		mlx_destroy_image(game->mlx, game->img_player);
	if (game->img_exit)
		mlx_destroy_image(game->mlx, game->img_exit);
	if (game->img_exit2)
		mlx_destroy_image(game->mlx, game->img_exit2);
	if (game->img_enemy)
		mlx_destroy_image(game->mlx, game->img_enemy);
	if (game->img_collectible)
		destroy_collectible(game);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free_map(game->map);
}
