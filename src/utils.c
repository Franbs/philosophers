/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 17:42:58 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/10/23 18:26:14 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	ft_check_atoi(const char *nptr)
{
	long long int	num;
	int				i;

	num = 0;
	i = 0;
	while (nptr[i])
	{
		if (num > (INT_MAX - (nptr[i] - '0')) / 10)
			return (false);
		num = num * 10 + (nptr[i] - '0');
		i++;
	}
	return (true);
}

int	ft_fill_data(int ac, char **av, t_data *data)
{
	data->n_philos = ft_atoi(av[1]);
	data->n_forks = ft_atoi(av[1]);
	data->die_time = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]);
	data->sleep_time = ft_atoi(av[4]);
	if (ac == 6)
		data->n_min_eat = ft_atoi(av[5]);
	else 
		data->n_min_eat = -1;
	data->is_dead = false;
	return (0);
}
