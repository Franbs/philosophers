/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:22:40 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/10/23 18:09:41 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_check_num(char *str)
{
	int	i;

	i = 0;
	if (*str == '\0')
		return (1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	if (!ft_check_atoi(str))
		return (1);
	return (0);
}

int	ft_check_args(int ac, char **av)
{
	int	i;

	if (ac != 5 && ac != 6)
		return (ft_printf("args not valid"), 1);
	i = 1;
	while (av[i])
	{
		if (ft_check_num(av[i]) == 1)
			return (ft_printf("args not valid"), 1);
		i++;
	}
	return (0);
}
