/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 12:29:00 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/18 16:58:40 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	handle_client(int client_fd, t_game *game, double *old_posx,
		double *old_posy)
{
	char	buffer[BUFFER_SIZE];
	double	current_x;
	double	current_y;
	ssize_t	write_result;

	ft_bzero(buffer, BUFFER_SIZE);
	pthread_mutex_lock(&game->server.mutex);
	current_x = _other()->posx;
	current_y = _other()->posy;
	pthread_mutex_unlock(&game->server.mutex);
	if (*old_posx != current_x || *old_posy != current_y)
	{
		snprintf(buffer, BUFFER_SIZE, "%.6f|%.6f", current_x, current_y);
		write_result = write(client_fd, buffer, ft_strlen(buffer));
		if (write_result < 0)
		{
			pthread_mutex_lock(&game->server.mutex);
			_other()->connected = 0;
			_other()->end2 = 1;
			pthread_mutex_unlock(&game->server.mutex);
			return ;
		}
		*old_posx = current_x;
		*old_posy = current_y;
	}
}

static int	wait_for_client_connection(t_game *game)
{
	fd_set			readfds;
	struct timeval	timeout;

	while (1)
	{
		pthread_mutex_lock(&game->server.mutex);
		if (_other()->end)
		{
			pthread_mutex_unlock(&game->server.mutex);
			return (0);
		}
		pthread_mutex_unlock(&game->server.mutex);
		FD_ZERO(&readfds);
		FD_SET(game->server.server_fd, &readfds);
		timeout.tv_sec = 0;
		timeout.tv_usec = 1000;
		if (select(game->server.server_fd + 1, &readfds,
				NULL, NULL, &timeout) > 0)
		{
			if (FD_ISSET(game->server.server_fd, &readfds))
				break ;
		}
	}
	return (1);
}

static int	accept_client_connection(t_game *game)
{
	game->server.client_fd = accept(game->server.server_fd,
			(struct sockaddr *)&game->server.client_addr,
			&game->server.addr_len);
	pthread_mutex_lock(&game->server.mutex);
	_other()->connected = 1;
	pthread_mutex_unlock(&game->server.mutex);
	if (game->server.client_fd < 0)
	{
		pthread_mutex_lock(&game->server.mutex);
		if (_other()->end)
		{
			pthread_mutex_unlock(&game->server.mutex);
			return (0);
		}
		pthread_mutex_unlock(&game->server.mutex);
		destroy_game_failure(game, "Failed to accept client connection");
	}
	printf("Client connected.\n");
	return (1);
}

static void	server_main_loop(t_game *game, double *old_posx, double *old_posy)
{
	while (1)
	{
		pthread_mutex_lock(&game->server.mutex);
		if (_other()->end || _other()->end2)
		{
			pthread_mutex_unlock(&game->server.mutex);
			break ;
		}
		pthread_mutex_unlock(&game->server.mutex);
		handle_client(game->server.client_fd, game, old_posx, old_posy);
		usleep(1000);
	}
}

void	*server_thread(void *data)
{
	t_game	*game;
	double	old_posx;
	double	old_posy;

	game = (t_game *)data;
	if (!wait_for_client_connection(game))
		return (NULL);
	if (!accept_client_connection(game))
		return (NULL);
	pthread_mutex_lock(&game->server.mutex);
	old_posx = _other()->posx;
	old_posy = _other()->posy;
	pthread_mutex_unlock(&game->server.mutex);
	send_map(game->server.client_fd, game);
	pthread_create(&_other()->read_thread, NULL, read_thread_func, game);
	server_main_loop(game, &old_posx, &old_posy);
	return (NULL);
}
