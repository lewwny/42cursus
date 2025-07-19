/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:03:15 by lengarci          #+#    #+#             */
/*   Updated: 2025/06/15 09:08:47 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

void	print_action(t_philo *philo, const char *action)
{
	long long	time;

	pthread_mutex_lock(&philo->data->print_lock);
	time = get_time_ms() - philo->data->start_time;
	if (!philo->data->is_dead)
		printf("%lld %d %s\n", time, philo->id, action);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	print_dead(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->data->state_lock);
	time = get_time_ms() - philo->data->start_time;
	printf("%lld %d died\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->state_lock);
}

int	thread_create(t_philo *philosophers, t_data *data)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	while (i < data->numbers_philo)
	{
		if (pthread_create(&philosophers[i].thread,
				NULL, routine, &philosophers[i]) != 0)
			return (0);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitoring, philosophers) != 0)
		return (0);
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < data->numbers_philo)
		pthread_join(philosophers[i++].thread, NULL);
	return (1);
}

int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->numbers_philo);
	if (!data->forks)
		return (0);
	i = 0;
	while (i < data->numbers_philo)
		pthread_mutex_init(&data->forks[i++], NULL);
	return (1);
}
