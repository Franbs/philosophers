/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:53:05 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/12/04 19:35:49 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*ft_philo_routine(void *arg)
{
	t_data	*data;
	t_philo	*philo;

	philo = (t_philo *)arg;
	data = philo->data;
	while (!ft_get_dead(data))
		ft_manage_routine(data, philo);
	return (NULL);
}

static void	ft_monitor_routine(t_data *data)
{
	while (!ft_get_dead(data))
	{
		ft_is_dead(data);
		ft_ate_min(data);
		usleep(1000);
	}
}

static int	ft_init_threads(t_data *data)
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
	ft_destroy_mutex_all(data);
	return (free(data->forks), free(data->philos), free(data), 0);
}
