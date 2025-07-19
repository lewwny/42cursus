/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:34:01 by lengarci          #+#    #+#             */
/*   Updated: 2025/07/18 17:11:52 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	handle_server_message(t_game *game, char *buffer,
			int bytes_received)
{
	if (bytes_received <= 0)
		return (-1);
	if (ft_strcmp(buffer, "END") == 0)
	{
		pthread_mutex_lock(&game->server.mutex);
		_other()->end2 = 1;
		pthread_mutex_unlock(&game->server.mutex);
		return (-1);
	}
	else if (ft_strcmp(buffer, "shot") == 0)
	{
		update_lifbar_state(game);
		return (0);
	}
	return (1);
}

static void	update_other_player_position(t_game *game, char *buffer)
{
	char	**pos;
	t_other	*other;

	other = _other();
	pos = ft_split(buffer, '|');
	if (!pos || !pos[0] || !pos[1])
	{
		if (pos)
			free_split(pos);
		destroy_game_failure(game, "Failed to parse position data from server");
	}
	pthread_mutex_lock(&game->server.mutex);
	other->otherposx = strtod(pos[0], NULL);
	other->otherposy = strtod(pos[1], NULL);
	free_split(pos);
	pthread_mutex_unlock(&game->server.mutex);
}

static int	read_position_from_server(t_game *game, char *buffer)
{
	int	bytes_received;
	int	handle_result;

	bytes_received = read_from_server_socket(game, buffer);
	if (bytes_received <= 0)
		return (bytes_received);
	handle_result = handle_server_message(game, buffer, bytes_received);
	if (handle_result < 0)
		return (-1);
	if (handle_result == 0)
		return (0);
	return (bytes_received);
}

static int	join_read_should_end(t_game *game)
{
	int	should_end;

	pthread_mutex_lock(&game->server.mutex);
	should_end = (_other()->end || _other()->end2);
	pthread_mutex_unlock(&game->server.mutex);
	return (should_end);
}

void	*join_read(void *arg)
{
	t_game			*game;
	char			buffer[BUFFER_SIZE];
	int				ret;

	game = (t_game *)arg;
	while (1)
	{
		if (join_read_should_end(game))
			break ;
		ret = read_position_from_server(game, buffer);
		if (ret == 0)
			continue ;
		if (ret < 0)
		{
			pthread_mutex_lock(&game->server.mutex);
			if (!_other()->end2)
				_other()->end2 = 1;
			pthread_mutex_unlock(&game->server.mutex);
			break ;
		}
		update_other_player_position(game, buffer);
	}
	close(game->sock);
	return (NULL);
}
