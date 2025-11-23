/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:09:30 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/11/23 02:25:16 by fbanzo-s         ###   ########.fr       */
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
