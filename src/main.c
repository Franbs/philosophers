/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:53:05 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/11/20 16:43:27 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_routine(void *arg)
{

}

ft_init_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		//pthread_create();
		i++;
	}
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
