/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:35:13 by lengarci          #+#    #+#             */
/*   Updated: 2025/06/11 17:57:28 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static bool	has_philo_eaten_enough(t_philo *philo, t_data *data, int i)
{
	bool	done_enough;

	done_enough = false;
	pthread_mutex_lock(&data->state_lock);
	if (philo[i].number_of_eat >= data->number_of_eat
		&& data->last_param)
		done_enough = true;
	pthread_mutex_unlock(&data->state_lock);
	return (done_enough);
}

static bool	has_philo_died(t_philo *philo, t_data *data, int i)
{
	bool	too_long;

	too_long = false;
	pthread_mutex_lock(&data->state_lock);
	if (get_time_ms() - philo[i].last_meal_time > data->time_to_die)
		too_long = true;
	pthread_mutex_unlock(&data->state_lock);
	return (too_long);
}

static int	check_philo_status(t_philo *philo, t_data *data, int *ok)
{
	int	i;

	i = 0;
	while (i < data->numbers_philo)
	{
		if (has_philo_eaten_enough(philo, data, i))
		{
			(*ok)++;
			i++;
			continue ;
		}
		if (has_philo_died(philo, data, i))
		{
			pthread_mutex_lock(&data->print_lock);
			data->is_dead = true;
			print_dead(&philo[i]);
			pthread_mutex_unlock(&data->print_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitoring(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	int		ok;

	philo = (t_philo *)arg;
	data = philo[0].data;
	while (1)
	{
		ok = 0;
		if (check_philo_status(philo, data, &ok))
			return (NULL);
		if (ok == data->numbers_philo)
			return (NULL);
		if (usleep(1000) != 0)
			return (NULL);
	}
	return (NULL);
}
