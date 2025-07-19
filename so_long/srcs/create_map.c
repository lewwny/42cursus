/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:37:39 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/05/07 10:54:24 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	load_collectible(t_game *game, int u)
{
	int		i;
	char	*filename;
	char	*number;
	char	*tmp;

	i = 0;
	game->num_collectible_frame = 11;
	game->img_collectible = malloc(sizeof(void *) * 11);
	if (!game->img_collectible)
		malloc_error(game->map);
	while (i < game->num_collectible_frame)
	{
		number = ft_itoa(i + 1);
		tmp = ft_strjoin("./img/", number);
		free(number);
		filename = ft_strjoin(tmp, ".xpm");
		free(tmp);
		game->img_collectible[i] = mlx_xpm_file_to_image(game->mlx,
				filename, &u, &u);
		free(filename);
		if (!game->img_collectible[i])
			error_load(game);
		i++;
	}
}

void	load_images(t_game *game)
{
	int	u;

	game->img_wall = mlx_xpm_file_to_image(game->mlx,
			"./img/tile-wall.xpm", &u, &u);
	game->img_player = mlx_xpm_file_to_image(game->mlx,
			"./img/sprite-player.xpm", &u, &u);
	game->img_floor = mlx_xpm_file_to_image(game->mlx,
			"./img/tile-floor.xpm", &u, &u);
	game->img_exit = mlx_xpm_file_to_image(game->mlx,
			"./img/chest1.xpm", &u, &u);
	game->img_exit2 = mlx_xpm_file_to_image(game->mlx,
			"./img/chest2.xpm", &u, &u);
	game->img_enemy = mlx_xpm_file_to_image(game->mlx,
			"./img/sprite-enemy.xpm", &u, &u);
	if (!game->img_wall || !game->img_player || !game->img_floor
		|| !game->img_exit || !game->img_exit2 || !game->img_enemy)
		error_load(game);
	load_collectible(game, u);
}

static void	collectible_player_enemy(t_game *game, int *x, int *y)
{
	if (game->map[*y][*x] == 'P')
		mlx_put_image_to_window(game->mlx,
			game->win, game->img_player, *x * TILE_SIZE, *y * TILE_SIZE);
	else if (game->map[*y][*x] == 'C')
		mlx_put_image_to_window(game->mlx,
			game->win, game->img_collectible[game->current_frame],
			*x * TILE_SIZE, *y * TILE_SIZE);
	else if (game->map[*y][*x] == 'e')
		mlx_put_image_to_window(game->mlx,
			game->win, game->img_exit2, *x * TILE_SIZE, *y * TILE_SIZE);
	else if (game->map[*y][*x] == 'M')
		mlx_put_image_to_window(game->mlx,
			game->win, game->img_enemy, *x * TILE_SIZE, *y * TILE_SIZE);
}

static void	put_count(t_game *game)
{
	char	*tmp;

	tmp = ft_itoa(game->move);
	if (!tmp)
		malloc_error2(game);
	mlx_string_put(game->mlx, game->win, 17, 40, 0xFFFFFF, tmp);
	free(tmp);
}

void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x + 1])
		{
			mlx_put_image_to_window(game->mlx,
				game->win, game->img_floor, x * TILE_SIZE, y * TILE_SIZE);
			if (game->map[y][x] == '1')
				mlx_put_image_to_window(game->mlx,
					game->win, game->img_wall, x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map[y][x] == 'E')
				mlx_put_image_to_window(game->mlx,
					game->win, game->img_exit, x * TILE_SIZE, y * TILE_SIZE);
			else
				collectible_player_enemy(game, &x, &y);
			x++;
		}
		y ++;
	}
	put_count(game);
}
