/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:11:42 by lengarci          #+#    #+#             */
/*   Updated: 2025/06/20 09:23:32 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_data
{
	int				numbers_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_eat;
	bool			last_param;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	state_lock;
	long long		start_time;
	bool			is_dead;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				number_of_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
	long long		last_meal_time;
	pthread_t		thread;
}	t_philo;

int			test_args(char **argv, int argc, t_data *data);
long long	get_time_ms(void);
void		init_args(t_data *data, char **argv);
void		print_action(t_philo *philo, const char *action);
void		print_dead(t_philo *philo);
void		*monitoring(void *arg);
int			init_philos(t_data *data);
void		*routine(void *arg);
int			thread_create(t_philo *philosophers, t_data *data);
int			init_forks(t_data *data);
int			ft_atoi(char *str);

#endif
