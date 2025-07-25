/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:38:47 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/18 16:59:40 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_oldmap(char **map, t_gb **garbage)
{
	int	i;

	if (!map || !*garbage || !map[0] || !garbage || !map[0][0])
		return ;
	i = 0;
	while (map[i])
	{
		_free(map[i], garbage);
		i++;
	}
	_free(map, garbage);
	map = NULL;
}

void	respawn_player(t_game *game)
{
	if (!game)
		return ;
	_other()->lifebar_state = 0;
	game->player.posx = game->spawnx;
	game->player.posy = game->spawny;
}

void	update_lifbar_state(t_game *game)
{
	t_other	*other;

	pthread_mutex_lock(&game->server.mutex);
	other = _other();
	if (other->lifebar_state < 4)
	{
		other->lifebar_state++;
		if (other->lifebar_state == 4)
		{
			game->menu_mode = 10;
			pthread_mutex_unlock(&game->server.mutex);
			raycasting(game);
			death_menu(game);
			return ;
		}
	}
	pthread_mutex_unlock(&game->server.mutex);
}
