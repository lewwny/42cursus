/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:32:27 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/05/15 08:31:54 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	close_game(t_game *game)
{
	int	i;

	mlx_destroy_image(game->mlx, game->img_wall);
	mlx_destroy_image(game->mlx, game->img_floor);
	mlx_destroy_image(game->mlx, game->img_player);
	mlx_destroy_image(game->mlx, game->img_exit);
	mlx_destroy_image(game->mlx, game->img_exit2);
	if (game->img_enemy)
		mlx_destroy_image(game->mlx, game->img_enemy);
	i = 0;
	while (i < game->num_collectible_frame)
	{
		mlx_destroy_image(game->mlx, game->img_collectible[i]);
		i++;
	}
	free(game->img_collectible);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free_map(game->map);
	free(game->mlx);
	exit(0);
}

static void	init_game(t_game *game)
{
	int	x_size;
	int	y_size;

	y_size = 0;
	game->mlx = mlx_init();
	if (!game->mlx)
		error_mlx(game);
	x_size = ft_strlen(game->map[0]) - 1;
	while (game->map[y_size])
		y_size++;
	game->win = mlx_new_window(game->mlx, x_size * TILE_SIZE,
			y_size * TILE_SIZE, "so_long");
	if (!game->win)
		error_mlx(game);
	load_images(game);
	render_map(game);
}

int	update_animation(t_game *game)
{
	static int	counter = 0;
	static int	counter_enemy = 0;
	static int	enemy = 0;

	counter++;
	counter_enemy++;
	if (counter >= 4000)
	{
		game->current_frame++;
		if (game->current_frame >= game->num_collectible_frame)
			game->current_frame = 0;
		render_map(game);
		counter = 0;
	}
	if (counter_enemy >= 20000)
	{
		if (game->enemy)
			move_enemy(game, &enemy);
		counter_enemy = 0;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	arg_error(argc, argv[1]);
	game.map = read_file(argv[1]);
	parse_map(&game);
	game.current_frame = 0;
	game.move = 0;
	init_game(&game);
	mlx_key_hook(game.win, handle_key, &game);
	mlx_loop_hook(game.mlx, update_animation, &game);
	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_loop(game.mlx);
	destroy_game(&game);
	return (0);
}
