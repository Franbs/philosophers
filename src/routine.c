/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 22:07:00 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/12/04 20:19:39 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_eat_sleep(t_philo *philo,
	pthread_mutex_t *f1, pthread_mutex_t *f2)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->data_lock);
	philo->meals_eaten++;
	philo->last_meal_time = ft_get_time();
	pthread_mutex_unlock(&data->data_lock);
	ft_log(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(f1);
	pthread_mutex_unlock(f2);
	ft_log(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

void	ft_manage_routine(t_data *data, t_philo *philo)
{
	pthread_mutex_t	*f1;
	pthread_mutex_t	*f2;

	ft_log(philo, "is thinking");
	if (philo->id == data->n_philos)
	{
		f1 = philo->right_fork;
		f2 = philo->left_fork;
	}
	else
	{
		f1 = philo->left_fork;
		f2 = philo->right_fork;
	}
	pthread_mutex_lock(f1);
	ft_log(philo, "has taken a fork");
	if (ft_get_dead(data))
	{
		pthread_mutex_unlock(f1);
		return ;
	}
	pthread_mutex_lock(f2);
	ft_log(philo, "has taken a fork");
	ft_eat_sleep(philo, f1, f2);
}

int	ft_manage_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_log(philo, "has taken a fork");
	ft_usleep(philo->data->time_to_die);
	pthread_mutex_unlock(philo->left_fork);
	ft_log(philo, "died");
	return (0);
}
