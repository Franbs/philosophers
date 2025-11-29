/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:09:30 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/11/29 22:48:57 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_lock_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_log(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	ft_log(philo, "has taken a fork");
}

void	ft_assign_forks(t_philo *philo, t_data *data)
{
	if (philo->id == data->n_philos)
	{
		philo->left_fork = &data->forks[philo->id - 1];
		philo->right_fork = &data->forks[0];
	}
	else
	{
		philo->left_fork = &data->forks[philo->id - 1];
		philo->right_fork = &data->forks[philo->id];
	}
}

void	ft_init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	if (!data->philos)
		return (ft_destroy_mutex_all(data), free(data->forks), free(data));
	i = 0;
	while (i < data->n_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = 0;
		data->philos[i].data = data;
		ft_assign_forks(&data->philos[i], data);
		i++;
	}
}

void	ft_is_dead(t_data *data)
{
	int		i;
	long	time_last_meal;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_lock(&data->data_lock);
		time_last_meal = ft_get_time()
			- data->philos[i].last_meal_time;
		pthread_mutex_unlock(&data->data_lock);
		if (time_last_meal > data->time_to_die)
		{
			ft_log(&data->philos[i], "died");
			pthread_mutex_lock(&data->data_lock);
			data->is_dead = true;
			pthread_mutex_unlock(&data->data_lock);
			return ;
		}
		i++;
	}
}

void	ft_ate_min(t_data *data)
{
	int	i;
	int	all_ate;

	if (data->n_min_eat <= 0)
		return ;
	all_ate = 1;
	pthread_mutex_lock(&data->data_lock);
	i = 0;
	while (i < data->n_philos)
	{
		if (data->philos[i].meals_eaten < data->n_min_eat)
		{
			all_ate = 0;
			break ;
		}
		i++;
	}
	if (all_ate == 1)
	{
		printf("all philosophers ate the min amount\n");
		data->is_dead = true;
	}
	pthread_mutex_unlock(&data->data_lock);
}
