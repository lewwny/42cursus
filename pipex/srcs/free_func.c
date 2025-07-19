/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:53:47 by lengarci          #+#    #+#             */
/*   Updated: 2025/05/15 13:58:36 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_cmd(char ***cmd, t_pipe *pipex)
{
	int	i;
	int	j;

	(void)pipex;
	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			free(cmd[i][j]);
			j++;
		}
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

void	free_split(char **tab, t_pipe *pipex)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	(void)pipex;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	free_split_n(char **tab, int n)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (i < n)
		free(tab[i++]);
	free(tab);
}
