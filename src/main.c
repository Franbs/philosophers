/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:53:05 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/11/17 19:53:10 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_init_forks(t_data *data)
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
	if (ft_init_forks(data) != 0)
		return (free(data), 1);
	ft_init_philos(data);
	return (free(data->forks), free(data->philos), free(data), 0);
}
