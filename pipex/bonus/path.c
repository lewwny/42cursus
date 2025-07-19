/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 08:42:29 by lengarci          #+#    #+#             */
/*   Updated: 2025/05/19 10:16:48 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_path(t_pipe *pipex, char *path)
{
	int		i;
	char	*tmp;

	path = path + 5;
	if (!path)
		path_error();
	pipex->paths = ft_split(path, ':');
	if (!pipex->paths)
		malloc_error(NULL);
	i = 0;
	while (pipex->paths[i])
	{
		tmp = ft_strjoin(pipex->paths[i], "/");
		if (!tmp)
			malloc_error(pipex);
		free(pipex->paths[i]);
		pipex->paths[i] = tmp;
		i++;
	}
}
