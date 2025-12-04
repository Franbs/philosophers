/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:09:30 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/12/04 19:39:38 by fbanzo-s         ###   ########.fr       */
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
	int		i;
	long	time_last_meal;
	long	curr_time;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_lock(&data->data_lock);
		time_last_meal = ft_get_time()
			- data->philos[i].last_meal_time;
		if (time_last_meal > data->time_to_die)
		{
			data->is_dead = true;
			pthread_mutex_unlock(&data->data_lock);
			pthread_mutex_lock(&data->write_lock);
			curr_time = ft_get_time() - data->start_time;
			printf("%ld %d died\n", curr_time, data->philos[i].id);
			pthread_mutex_unlock(&data->write_lock);
			return ;
		}
		pthread_mutex_unlock(&data->data_lock);
		i++;
	}
}

static int	ft_check_ate_min(t_data *data)
{
	int	i;
	int	all_ate;

	all_ate = 1;
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
	return (all_ate);
}

void	ft_ate_min(t_data *data)
{
	int	all_ate;

	if (data->n_min_eat <= 0)
		return ;
	pthread_mutex_lock(&data->data_lock);
	all_ate = ft_check_ate_min(data);
	if (all_ate == 1)
	{
		data->is_dead = true;
		pthread_mutex_unlock(&data->data_lock);
		pthread_mutex_lock(&data->write_lock);
		printf("all philosophers ate the min amount\n");
		pthread_mutex_unlock(&data->write_lock);
		return ;
	}
	pthread_mutex_unlock(&data->data_lock);
}
