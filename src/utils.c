/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 17:42:58 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/11/23 02:27:33 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atol(const char *nptr)
{
	long	sign;
	long	num;

	if (!nptr)
		return (0);
	num = 0;
	sign = 1;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n'
		|| *nptr == '\r' || *nptr == '\v' || *nptr == '\f')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr && ft_isdigit(*nptr))
	{
		num = num * 10 + (*nptr - '0');
		nptr++;
	}
	return (num * sign);
}

int	ft_atoi(const char *nptr)
{
	long			sign;
	long long int	num;

	if (!nptr)
		return (0);
	num = 0;
	sign = 1;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n'
		|| *nptr == '\r' || *nptr == '\v' || *nptr == '\f')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr && ft_isdigit(*nptr))
	{
		num = num * 10 + (*nptr - '0');
		nptr++;
	}
	return ((int)num * sign);
}

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

long	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long time)
{
	long	start_time;

	start_time = ft_get_time();
	while ((ft_get_time() - start_time) < time)
		usleep(500);
}
