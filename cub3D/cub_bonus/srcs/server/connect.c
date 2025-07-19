/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:22:08 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/16 12:15:13 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	set_socket_nonblocking(int sock, int *flags)
{
	*flags = fcntl(sock, F_GETFL, 0);
	if (*flags < 0)
		return (-1);
	if (fcntl(sock, F_SETFL, *flags | O_NONBLOCK) < 0)
		return (-1);
	return (0);
}

static int	wait_for_socket_writable(int sock, int timeout_sec)
{
	fd_set			write_fds;
	struct timeval	timeout;
	int				result;

	FD_ZERO(&write_fds);
	FD_SET(sock, &write_fds);
	timeout.tv_sec = timeout_sec;
	timeout.tv_usec = 0;
	result = select(sock + 1, NULL, &write_fds, NULL, &timeout);
	if (result == 0)
	{
		errno = ETIMEDOUT;
		return (-1);
	}
	if (result < 0)
		return (-1);
	return (0);
}

static int	check_connect_result(int sock, int flags, int timeout_sec)
{
	int				error;
	socklen_t		len;

	if (wait_for_socket_writable(sock, timeout_sec) < 0)
		return (-1);
	len = sizeof(error);
	if (getsockopt(sock, SOL_SOCKET, SO_ERROR, &error, &len) < 0)
		return (-1);
	if (error != 0)
	{
		errno = error;
		return (-1);
	}
	fcntl(sock, F_SETFL, flags);
	return (0);
}

static int	connect_with_timeout(int sock, struct sockaddr_in *server_addr,
		int timeout_sec)
{
	int	flags;
	int	result;

	if (set_socket_nonblocking(sock, &flags) < 0)
		return (-1);
	result = connect(sock, (struct sockaddr *)server_addr,
			sizeof(*server_addr));
	if (result == 0)
	{
		fcntl(sock, F_SETFL, flags);
		return (0);
	}
	if (errno != EINPROGRESS)
		return (-1);
	return (check_connect_result(sock, flags, timeout_sec));
}

void	connect_to_server(t_game *game, char **argv)
{
	struct sockaddr_in	server_addr;

	game->sock = socket(AF_INET, SOCK_STREAM, 0);
	if (game->sock < 0)
		destroy_game_failure(game, "Failed to create socket");
	ft_bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(ft_atoi(argv[3]));
	printf("Connecting to server %s:%s\n", argv[2], argv[3]);
	if (ft_strcmp(argv[2], "localhost") == 0)
		server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	else if (inet_pton(AF_INET, argv[2], &server_addr.sin_addr) <= 0)
		destroy_game_failure(game, "Invalid address/ Address not supported");
	if (connect_with_timeout(game->sock, &server_addr, 1) < 0)
	{
		if (errno == ETIMEDOUT)
			destroy_game_failure(game,
				"Cannot join server : a game is already in progress");
		else
			destroy_game_failure(game, "Connection failed");
	}
	printf("Connected to server %s:%s\n", argv[2], argv[3]);
}
