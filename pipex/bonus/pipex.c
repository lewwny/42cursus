/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:48:07 by lengarci          #+#    #+#             */
/*   Updated: 2025/05/22 14:35:38 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exec_cmd(t_pipe *pipex, char **envp, int i)
{
	if (pipex->path_cmd[i])
		execve(pipex->path_cmd[i], pipex->cmd[i], envp);
	ft_puterror("Error\nCommand <");
	ft_puterror(pipex->cmd[i][0]);
	ft_puterror("> does not found\n");
	free_cmd(pipex->cmd, pipex);
	free_split_n(pipex->path_cmd, pipex->cmd_count);
	free_split(pipex->paths, pipex);
	close(pipex->fd_infile);
	if (pipex->fd_outfile > 0)
		close(pipex->fd_outfile);
	exit(127);
}

static void	son_program(t_pipe *pipex, char **envp, int input_fd, int output_fd)
{
	dup2(input_fd, 0);
	dup2(output_fd, 1);
	close(input_fd);
	close(output_fd);
	close(pipex->fd_infile);
	exec_cmd(pipex, envp, pipex->i);
}

static void	last_pipe(t_pipe *pipex, int pipe_in, char **envp, pid_t *pid)
{
	*pid = fork();
	if (*pid == 0)
		son_program(pipex, envp, pipe_in, pipex->fd_outfile);
	close(pipe_in);
	close(pipex->fd_outfile);
}

static void	end_func(t_pipe *pipex, int *pipe_in, char **envp, pid_t *pid)
{
	if (pipex ->fd_outfile == -1)
		file_error2(pipex, pipex->fd);
	last_pipe(pipex, *pipe_in, envp, pid);
	while (wait(NULL) < 0)
	{
	}
}

void	pipex_func(t_pipe *pipex, char **envp, char **argv, int argc)
{
	int		pipe_in;
	pid_t	pid;

	pipex->i = pipex->test + 0;
	pipe_in = pipex->fd_infile;
	while (pipex->i < pipex->cmd_count - 1)
	{
		if (pipe(pipex->fd) == -1)
			error_pipe(pipex);
		pid = fork();
		if (pid == 0)
		{
			close(pipex->fd[0]);
			son_program(pipex, envp, pipe_in, pipex->fd[1]);
		}
		close(pipex->fd[1]);
		if (pipe_in != pipex->fd_infile)
			close(pipe_in);
		pipe_in = pipex->fd[0];
		pipex->i++;
	}
	pipex->fd_outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC,
			0644);
	end_func(pipex, &pipe_in, envp, &pid);
}
