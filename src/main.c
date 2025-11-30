/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:53:05 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/11/30 22:21:03 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_philo_routine(void *arg)
{
	t_data	*data;
	t_philo	*philo;
	bool	dead;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	data = philo->data;
	pthread_mutex_lock(&data->data_lock);
	dead = data->is_dead;
	pthread_mutex_unlock(&data->data_lock);
	while (!dead)
	{
		ft_manage_routine(data, philo);
		pthread_mutex_lock(&data->data_lock);
		dead = data->is_dead;
		pthread_mutex_unlock(&data->data_lock);
	}
	return (NULL);
}

void	ft_monitor_routine(t_data *data)
{
	bool	dead;

	pthread_mutex_lock(&data->data_lock);
	dead = data->is_dead;
	pthread_mutex_unlock(&data->data_lock);
	while (!dead)
	{
		ft_is_dead(data);
		ft_ate_min(data);
		pthread_mutex_lock(&data->data_lock);
		dead = data->is_dead;
		pthread_mutex_unlock(&data->data_lock);
		usleep(1000);
	}
}

int	ft_init_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = ft_get_time();
	if (data->n_philos == 1)
		return (ft_manage_one_philo(&data->philos[0]));
	while (i < data->n_philos)
	{
		data->philos[i].last_meal_time = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL,
				ft_philo_routine, &data->philos[i]) != 0)
			return (1);
		i++;
	}
	ft_monitor_routine(data);
	i = 0;
	while (i < data->n_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ft_check_args(ac, av) == 1)
		return (1);
	data = ft_init_data(ac, av);
	if (!data)
		return (1);
	if (ft_init_mutex_forks(data) != 0)
		return (free(data), 1);
	ft_init_philos(data);
	ft_init_threads(data);
	return (free(data->forks), free(data->philos), free(data), 0);
}
