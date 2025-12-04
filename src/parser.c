/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:22:40 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/12/05 00:08:51 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	ft_check_atol(const char *nptr)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while (nptr[i])
	{
		if (result > LONG_MAX / 10)
			return (false);
		result *= 10;
		if (result > LONG_MAX - (nptr[i] - '0'))
			return (false);
		result += nptr[i] - '0';
		i++;
	}
	if (result <= 0)
		return (false);
	if (result > INT_MAX)
		return (false);
	return (true);
}

static int	ft_check_num(char *str)
{
	int	i;

	i = 0;
	if (!str || str[i] == '\0')
		return (1);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	if (!ft_check_atol(str))
		return (1);
	return (0);
}

int	ft_check_args(int ac, char **av)
{
	int	i;

	if (ac != 5 && ac != 6)
		return (printf("args not valid\n"), 1);
	if (ft_atol(av[1]) > 200)
		return (printf("args not valid\n"), 1);
	i = 1;
	while (av[i])
	{
		if (ft_check_num(av[i]) == 1)
			return (printf("args not valid\n"), 1);
		i++;
	}
	return (0);
}

void	ft_log(t_philo *philo, char *msg)
{
	t_data	*data;
	long	curr_time;

	data = philo->data;
	pthread_mutex_lock(&data->write_lock);
	if (!ft_get_dead(data))
	{
		curr_time = ft_get_time() - data->start_time;
		printf("%ld %d %s\n", curr_time, philo->id, msg);
	}
	pthread_mutex_unlock(&data->write_lock);
}
