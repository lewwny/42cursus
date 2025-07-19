/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:17:27 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/05/22 14:22:53 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef struct s_pipe
{
	int		fd_infile;
	int		fd_outfile;
	int		cmd_count;
	int		status;
	int		test;
	char	**paths;
	char	**path_cmd;
	char	***cmd;
}	t_pipe;

void	test_arg(int argc, char **argv);
void	file_error(void);
void	file_error2(t_pipe *pipex);
void	open_files(t_pipe *pipex, char **argv);
void	get_path(t_pipe *pipex, char *path);
void	path_error(void);
void	malloc_error(t_pipe *pipex);
void	take_commands(t_pipe *pipex, int argc, char **argv);
void	free_cmd(char ***cmd, t_pipe *pipex);
void	free_split(char **tab, t_pipe *pipex);
void	error_pipe(t_pipe *pipex);
void	pipex_func(t_pipe *pipex, char **envp, char **argv);
void	ft_puterror(char *str);
void	free_split_n(char **tab, int n);

#endif
