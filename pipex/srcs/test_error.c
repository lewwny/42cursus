/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:58:42 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/05/13 14:14:49 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	test_arg(int argc, char **argv)
{
	int	i;

	if (argc != 5)
	{
		ft_printf("Error, use : ./pipex file1 cmd1 cmd2 file2\n");
		exit(1);
	}
	i = 0;
	while (argv[i])
	{
		if (argv[i][0] == '\0')
		{
			ft_printf("Error\nEmpty argument\n");
			exit(1);
		}
		i++;
	}
}
