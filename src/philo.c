/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:09:30 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/11/17 19:49:29 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_assign_forks(t_philo *philo, t_data *data)
{
	if (philo->id == data->n_philos - 1)
	{
		philo->left_fork = &data->forks[philo->id];
		philo->right_fork = &data->forks[data->n_philos - 1];
	}
	else
	{
		philo->left_fork = &data->forks[philo->id];
		philo->right_fork = &data->forks[philo->id + 1];
	}
}

void	ft_init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		data->philos[i].id = i;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = 0;
		data->philos[i].data = data;
		ft_assign_forks(&data->philos[i], data);
		i++;
	}
}
