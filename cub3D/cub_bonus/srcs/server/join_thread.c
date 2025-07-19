/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:03:04 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/18 17:11:58 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	close_sockets(t_game *game)
{
	if (game->host)
	{
		if (game->server.server_fd > 0)
		{
			close(game->server.server_fd);
			game->server.server_fd = -1;
		}
		if (game->server.client_fd > 0)
		{
			close(game->server.client_fd);
			game->server.client_fd = -1;
		}
	}
	if (game->join && game->sock > 0)
	{
		close(game->sock);
		game->sock = -1;
	}
}

void	join_thread(t_game *game)
{
	if (game->host || game->join)
	{
		pthread_mutex_lock(&game->server.mutex);
		_other()->end = 1;
		pthread_mutex_unlock(&game->server.mutex);
		if (game->join)
		{
			pthread_join(_other()->join_writee, NULL);
			pthread_join(_other()->join_reade, NULL);
		}
		else if (game->host)
		{
			pthread_join(_other()->server, NULL);
			pthread_join(_other()->read_thread, NULL);
		}
		close_sockets(game);
	}
}

int	read_from_server_socket(t_game *game, char *buffer)
{
	fd_set			readfds;
	struct timeval	timeout;
	int				bytes_received;

	FD_ZERO(&readfds);
	FD_SET(game->sock, &readfds);
	timeout.tv_sec = 0;
	timeout.tv_usec = 1000;
	if (select(game->sock + 1, &readfds, NULL, NULL, &timeout) <= 0)
		return (0);
	if (!FD_ISSET(game->sock, &readfds))
		return (0);
	bytes_received = read(game->sock, buffer, BUFFER_SIZE - 1);
	if (bytes_received <= 0)
		return (-1);
	buffer[bytes_received] = '\0';
	return (bytes_received);
}
