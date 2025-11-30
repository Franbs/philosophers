/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 22:07:00 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/11/30 22:20:57 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_manage_routine(t_data *data, t_philo *philo)
{
	ft_log(philo, "is thinking");
	ft_lock_forks(philo);
	pthread_mutex_lock(&data->data_lock);
	ft_log(philo, "is eating");
	philo->meals_eaten++;
	philo->last_meal_time = ft_get_time();
	pthread_mutex_unlock(&data->data_lock);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	ft_log(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
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

void	ft_lock_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_log(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	ft_log(philo, "has taken a fork");
}
