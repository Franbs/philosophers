/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 22:39:14 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/11/19 14:19:48 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_destroy_mutex_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	data->forks = NULL;
}

void	ft_destroy_mutex_all(t_data *data)
{
	pthread_mutex_destroy(&data->data_lock);
	pthread_mutex_destroy(&data->write_lock);
	ft_destroy_mutex_forks(data);
}

int	ft_init_mutex_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->forks)
		return (free(data), 1);
	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->data_lock, NULL) != 0)
		return (ft_destroy_mutex_forks(data), 1);
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&data->data_lock);
		return (ft_destroy_mutex_forks(data), 1);
	}
	return (0);
}
