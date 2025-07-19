/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenygarcia <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:57:22 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/05/12 14:42:31 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	fill_tmp(int *i, char **map, char **tmp, int *count)
{
	*i = 0;
	while (*i < *count)
	{
		tmp[*i] = map[*i];
		(*i)++;
	}
}

static char	**read_file_to_map(int fd)
{
	char	**map;
	char	*line;
	int		count;
	int		i;
	char	**tmp;

	map = NULL;
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		tmp = malloc(sizeof(char *) * (count + 2));
		if (!tmp)
			malloc_error(NULL);
		fill_tmp(&i, map, tmp, &count);
		tmp[count] = line;
		tmp[count + 1] = NULL;
		if (map)
			free(map);
		map = tmp;
		count++;
		line = get_next_line(fd);
	}
	return (map);
}

char	**read_file(char *file)
{
	char	**map;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		wrong_file();
	map = read_file_to_map(fd);
	if (!map)
	{
		ft_printf("Error\nMauvaise lecture du fichier\n");
		exit(1);
	}
	close(fd);
	return (map);
}
