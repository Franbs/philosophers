/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:09:30 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/11/25 19:48:31 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		if (ft_get_time() - data->philos[i].last_meal_time
			> data->time_to_die)
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
	int		i;

	if (data->n_min_eat <= 0)
		return ;
	i = 0;
	while (i < data->n_philos)
	{
		if (data->philos[i].meals_eaten < data->n_min_eat)
			return ;
		i++;
	}
	printf("all philosophers ate the min amount\n");
	pthread_mutex_lock(&data->data_lock);
	data->is_dead = true;
	pthread_mutex_unlock(&data->data_lock);
}
