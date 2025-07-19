/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macauchy <macauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:46:02 by macauchy          #+#    #+#             */
/*   Updated: 2025/07/16 12:49:50 by macauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	can_move_axis(t_game *game, double x, double y, double buffer)
{
	double	corners[4][2];
	int		mx;
	int		my;
	int		i;

	corners[0][0] = x + buffer;
	corners[0][1] = y + buffer;
	corners[1][0] = x - buffer;
	corners[1][1] = y - buffer;
	corners[2][0] = x + buffer;
	corners[2][1] = y - buffer;
	corners[3][0] = x - buffer;
	corners[3][1] = y + buffer;
	i = 0;
	while (i < 4)
	{
		mx = (int)corners[i][0];
		my = (int)corners[i][1];
		if (mx < 0 || my < 0 || mx >= game->width || my >= game->height
			|| game->final_map[my][mx] == '1')
			return (0);
		i++;
	}
	return (1);
}
