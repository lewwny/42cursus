/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:17:58 by lengarci          #+#    #+#             */
/*   Updated: 2025/06/20 09:21:02 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (!test_args(argv, argc, &data))
		return (1);
	init_args(&data, argv);
	data.start_time = get_time_ms();
	if (data.number_of_eat < 1 && data.last_param)
	{
		pthread_mutex_destroy(&data.print_lock);
		pthread_mutex_destroy(&data.state_lock);
		return (0);
	}
	if (!init_philos(&data))
	{
		write(2, "Error initializing philosophers\n", 33);
		pthread_mutex_destroy(&data.print_lock);
		pthread_mutex_destroy(&data.state_lock);
		free(data.forks);
		data.forks = NULL;
		return (1);
	}
	pthread_mutex_destroy(&data.print_lock);
	pthread_mutex_destroy(&data.state_lock);
	return (0);
}
