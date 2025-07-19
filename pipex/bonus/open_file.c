/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:09:32 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/05/22 14:28:56 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_files(t_pipe *pipex, char **argv)
{
	pipex->fd_infile = open(argv[1], O_RDONLY);
	if (pipex->fd_infile == -1)
	{
		ft_puterror("Error\nA file can't be open\n");
		pipex->fd_infile = open("/dev/null", O_RDONLY);
		pipex->test = 1;
	}
}
