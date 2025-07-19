/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:31:30 by lengarci          #+#    #+#             */
/*   Updated: 2025/05/19 10:16:07 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	malloc_and_create_cmd(t_pipe *pipex, int argc, char **argv)
{
	int	i;

	i = 0;
	pipex->cmd_count = argc - 3;
	pipex->cmd = malloc(sizeof(char **) * (pipex->cmd_count + 1));
	if (!pipex->cmd)
		malloc_error(NULL);
	while (i < pipex->cmd_count)
	{
		pipex->cmd[i] = ft_split(argv[i + 2], ' ');
		if (!pipex->cmd[i])
		{
			pipex->cmd[i] = NULL;
			malloc_error(pipex);
		}
		i++;
	}
	pipex->cmd[i] = NULL;
}

static char	*test_path(char *cmd, char **paths, t_pipe *pipex)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], cmd);
		if (!tmp)
			malloc_error(pipex);
		if (access(tmp, X_OK) == 0)
			return (tmp);
		free(tmp);
		i++;
	}
	return (NULL);
}

static void	take_path_command(t_pipe *pipex)
{
	int		i;
	char	*tmp;

	i = 0;
	pipex->path_cmd = malloc(sizeof(char *) * (pipex->cmd_count + 1));
	if (!pipex->path_cmd)
		malloc_error(pipex);
	ft_bzero(pipex->path_cmd, sizeof(char *) * (pipex->cmd_count + 1));
	while (i < pipex->cmd_count)
	{
		tmp = test_path(pipex->cmd[i][0], pipex->paths, pipex);
		pipex->path_cmd[i] = tmp;
		i++;
	}
	pipex->path_cmd[i] = NULL;
}

void	take_commands(t_pipe *pipex, int argc, char **argv)
{
	malloc_and_create_cmd(pipex, argc, argv);
	take_path_command(pipex);
}
