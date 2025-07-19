/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:57:36 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/05/22 14:34:58 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	exit_program(t_pipe *pipex)
{
	int	i;

	i = 0;
	while (pipex->paths[i])
		free(pipex->paths[i++]);
	free(pipex->paths);
	close(pipex->fd_infile);
	free_cmd(pipex->cmd, pipex);
	free_split_n(pipex->path_cmd, pipex->cmd_count);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	pipex;
	int		i;

	pipex.test = 0;
	ft_bzero(&pipex, sizeof(pipex));
	test_arg(argc, argv);
	open_files(&pipex, argv);
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		path_error();
	get_path(&pipex, envp[i]);
	take_commands(&pipex, argc, argv);
	pipex_func(&pipex, envp, argv);
	exit_program(&pipex);
	return (WEXITSTATUS(pipex.status));
}
