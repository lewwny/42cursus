/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:48:07 by lengarci          #+#    #+#             */
/*   Updated: 2025/05/22 14:40:23 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_puterror(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(2, str, i);
}

static void	exec_cmd(t_pipe *pipex, char **envp, int i, int *fd)
{
	close(pipex->fd_infile);
	if (i)
		close(pipex->fd_outfile);
	if (pipex->path_cmd[i])
		execve(pipex->path_cmd[i], pipex->cmd[i], envp);
	ft_puterror("Error\nCommand <");
	ft_puterror(pipex->cmd[i][0]);
	ft_puterror("> does not found\n");
	free_cmd(pipex->cmd, pipex);
	free_split_n(pipex->path_cmd, pipex->cmd_count);
	free_split(pipex->paths, pipex);
	close(fd[0]);
	close(fd[1]);
	close(pipex->fd_infile);
	exit(127);
}

static void	son_program(t_pipe *pipex, int *fd, int n, char **envp)
{
	dup2(pipex->fd_infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	exec_cmd(pipex, envp, n, fd);
}

static void	file_error22(t_pipe *pipex, int *fd)
{
	close(fd[0]);
	close(fd[1]);
	file_error2(pipex);
}

void	pipex_func(t_pipe *pipex, char **envp, char **argv)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) == -1)
		error_pipe(pipex);
	pid1 = fork();
	if (pid1 == 0 && !pipex->test)
		son_program(pipex, fd, 0, envp);
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		pipex->fd_outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (pipex->fd_outfile == -1)
			file_error22(pipex, fd);
		dup2(pipex->fd_outfile, STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		exec_cmd(pipex, envp, 1, fd);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &pipex->status, 0);
}
