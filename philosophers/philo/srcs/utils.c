/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:21:05 by lengarci          #+#    #+#             */
/*   Updated: 2025/06/20 09:23:21 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_atoi(char *str)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	while (str[i])
		res = res * 10 + (str[i++] - 48);
	return (res);
}

void	init_args(t_data *data, char **argv)
{
	pthread_mutex_init(&data->state_lock, NULL);
	pthread_mutex_init(&data->print_lock, NULL);
	data->numbers_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->last_param)
		data->number_of_eat = ft_atoi(argv[5]);
	else
		data->number_of_eat = -1;
}
