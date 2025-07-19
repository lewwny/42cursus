/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:47:00 by lengarci          #+#    #+#             */
/*   Updated: 2025/06/15 10:41:15 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	handle_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	if (usleep(philo->data->time_to_die * 1000) != 0)
		return (0);
	pthread_mutex_unlock(philo->left_fork);
	return (1);
}

static void	philo_take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->id % 2 == 0)
		usleep(1000);
	if (philo->left_fork < philo->right_fork)
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	else
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	pthread_mutex_lock(first);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(second);
	print_action(philo, "has taken a fork");
}

static int	philo_eat(t_philo *philo)
{
	philo_take_forks(philo);
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->data->state_lock);
	philo->number_of_eat++;
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->data->state_lock);
	if (usleep(philo->data->time_to_eat * 1000) != 0)
		return (0);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	if (philo->data->last_param && philo->number_of_eat
		>= philo->data->number_of_eat)
		return (0);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->numbers_philo == 1)
	{
		handle_one_philo(philo);
		return (NULL);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->data->state_lock);
		if (philo->data->is_dead)
		{
			pthread_mutex_unlock(&philo->data->state_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->state_lock);
		if (!philo_eat(philo))
			return (NULL);
		print_action(philo, "is sleeping");
		if (usleep(philo->data->time_to_sleep * 1000) != 0)
			return (NULL);
		print_action(philo, "is thinking");
	}
	return (NULL);
}
