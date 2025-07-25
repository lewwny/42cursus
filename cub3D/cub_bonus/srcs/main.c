/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:22:48 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/18 18:56:44 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	game_loop(t_game *game)
{
	if (game->keys.esc)
	{
		pause_menu(game);
		game->keys.esc = 0;
	}
	handle_movement(game);
	handle_rotation(game);
	handle_sprint(game);
	handle_shoot_animation(game);
	handle_crosshair_animation(game);
	game->delta_time = get_delta_time();
	fov_sprint(game);
	if (game->menu_mode == 4)
		raycasting(game);
	if (game->host || game->join)
	{
		pthread_mutex_lock(&game->server.mutex);
		_other()->posx = game->player.posx;
		_other()->posy = game->player.posy;
		pthread_mutex_unlock(&game->server.mutex);
	}
	return (0);
}

static void	init_game(t_game *game, int argc, char **argv)
{
	ft_bzero(game, sizeof(t_game));
	ft_bzero(&game->player.ray, sizeof(t_ray));
	game->cache_initialized = 0;
	parsing(argc, argv, game);
	init_player(game);
	game->spawnx = game->player.posx;
	game->spawny = game->player.posy;
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
	{
		ft_dprintf(2, "Error: Failed to initialize MLX.\n");
		exit(EXIT_FAILURE);
	}
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIDTH, HEIGHT, "cub3d");
	if (!game->win_ptr)
	{
		ft_dprintf(2, "Error: Failed to create a new window.\n");
		free(game->mlx_ptr);
		exit(EXIT_FAILURE);
	}
	game->width = WIDTH;
	game->height = HEIGHT;
	game->cam_angle = atan2(game->player.diry, game->player.dirx);
	game->cam_target = atan2(game->player.dirx, -game->player.diry);
}

static int	close_game(t_game *game)
{
	destroy_game(game);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_game		game;

	signal(SIGPIPE, SIG_IGN);
	printf ("Welcome to cub3d!\n");
	printf("Host usage : ./cub3d <map_file> --host\n");
	printf("Join usage : ./cub3d --join <ip_address> <port>\n");
	init_game(&game, argc, argv);
	if (game.host)
	{
		init_server(&game);
		pthread_create(&_other()->server, NULL, server_thread, &game);
		pthread_mutex_init(&game.server.mutex, NULL);
	}
	load_img(&game);
	mlx_hook(game.win_ptr, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win_ptr, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win_ptr, 6, 1L << 6, on_mouse_move, &game);
	mlx_hook(game.win_ptr, 4, 1L << 2, on_mouse_click, &game);
	mlx_hook(game.win_ptr, 17, 0, close_game, &game);
	mlx_loop_hook(game.mlx_ptr, game_loop, &game);
	mlx_loop(game.mlx_ptr);
	destroy_game(&game);
}
