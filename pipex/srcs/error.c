/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:08:00 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/05/22 08:19:48 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	file_error(void)
{
	ft_puterror("Error\nA file can't be open\n");
	exit(1);
}

void	path_error(void)
{
	ft_puterror("Error\nPath error\n");
	exit(1);
}

void	malloc_error(t_pipe *pipex)
{
	if (pipex)
	{
		if (pipex->cmd)
			free_cmd(pipex->cmd, pipex);
		if (pipex->paths)
			free_split(pipex->paths, pipex);
		if (pipex->path_cmd)
			free_split_n(pipex->path_cmd, pipex->cmd_count);
	}
	ft_puterror("Error\nMalloc error\n");
	exit(1);
}

void	error_pipe(t_pipe *pipex)
{
	if (pipex->cmd)
		free_cmd(pipex->cmd, pipex);
	if (pipex->paths)
		free_split(pipex->paths, pipex);
	if (pipex->path_cmd)
		free_split_n(pipex->path_cmd, pipex->cmd_count);
	ft_puterror("Error\nPipe error\n");
	exit(1);
}

void	file_error2(t_pipe *pipex)
{
	if (pipex)
	{
		if (pipex->cmd)
			free_cmd(pipex->cmd, pipex);
		if (pipex->paths)
			free_split(pipex->paths, pipex);
		if (pipex->path_cmd)
			free_split_n(pipex->path_cmd, pipex->cmd_count);
	}
	close(pipex->fd_infile);
	ft_puterror("Error\nA file can't be open\n");
	exit(1);
}
