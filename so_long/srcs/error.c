/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:53:28 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/05/06 12:01:13 by lenygarcia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	invalid_map(char **map)
{
	ft_printf("Error\nInvalid map\n");
	free_map(map);
	exit(1);
}

void	malloc_error(char **map)
{
	if (map)
		free_map(map);
	ft_printf("Error\nProblème d'allocation mémoire\n");
	exit(1);
}

void	wrong_file(void)
{
	ft_printf("Error\nLe fichier est illisible ou introuvable\n");
	exit(1);
}

void	file_error(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(file + len - 4, ".ber", 4) != 0)
	{
		ft_printf("Error\nMauvais format de map\n");
		exit(1);
	}
}

void	arg_error(int argc, char *file)
{
	if (argc == 1)
	{
		ft_printf("Error\nVeuillez donner au programme une map en argument\n");
		exit(1);
	}
	if (argc > 2)
	{
		ft_printf("Error\n");
		ft_printf("Veuillez ne pas donner plus d'un argument au programme\n");
		exit(1);
	}
	file_error(file);
}
