/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:53:05 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/11/22 20:27:12 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->data->is_dead == false)
	{
		
	}
}

int	ft_init_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = ft_get_time();
	while (i < data->n_philos)
	{
		data->philos[i].last_meal_time = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL,
			philo_routine, &data->philos[i]) != 0)
			return (1);
		i++;
	}
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
