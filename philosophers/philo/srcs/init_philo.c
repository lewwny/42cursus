/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:44:46 by lengarci          #+#    #+#             */
/*   Updated: 2025/06/11 18:03:26 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	init_philo_structs(t_philo *philosophers,
	t_data *data, pthread_t *thread)
{
	int	i;

	i = 0;
	while (i < data->numbers_philo)
	{
		philosophers[i].id = i + 1;
		philosophers[i].data = data;
		philosophers[i].last_meal_time = data->start_time;
		philosophers[i].left_fork = &data->forks[i];
		philosophers[i].right_fork = &data->forks[(i + 1)
			% data->numbers_philo];
		philosophers[i].thread = thread[i];
		philosophers[i].number_of_eat = 0;
		i++;
	}
}

static void	cleanup_resources(t_data *data, t_philo *philosophers,
		pthread_t *thread)
{
	int	i;

	i = 0;
	while (i < data->numbers_philo)
		pthread_mutex_destroy(&data->forks[i++]);
	free(data->forks);
	free(philosophers);
	free(thread);
}

static int	alloc_philos_and_threads(t_data *data, t_philo **philosophers,
		pthread_t **thread)
{
	*philosophers = malloc(sizeof(t_philo) * data->numbers_philo);
	if (!*philosophers)
		return (0);
	*thread = malloc(sizeof(pthread_t) * data->numbers_philo);
	if (!*thread)
	{
		free(*philosophers);
		return (0);
	}
	return (1);
}

static int	init_and_run_threads(t_data *data, t_philo *philosophers,
		pthread_t *thread)
{
	init_philo_structs(philosophers, data, thread);
	if (!thread_create(philosophers, data))
		return (0);
	return (1);
}

int	init_philos(t_data *data)
{
	t_philo		*philosophers;
	pthread_t	*thread;

	if (!alloc_philos_and_threads(data, &philosophers, &thread))
		return (0);
	if (!init_forks(data))
	{
		free(philosophers);
		free(thread);
		return (0);
	}
	if (!init_and_run_threads(data, philosophers, thread))
	{
		cleanup_resources(data, philosophers, thread);
		return (0);
	}
	cleanup_resources(data, philosophers, thread);
	return (1);
}
