/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:51:38 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/10/23 18:23:16 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "../libft/libft.h"
# include <stdio.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_data t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				meals_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				n_philos;
	int				eat_time;
	int				die_time;
	int				sleep_time;
	int				n_forks;
	int				n_min_eat;
	bool			is_dead;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	
}	t_data;

// utils.c
bool	ft_check_atoi(const char *nptr);
int		ft_fill_data(int ac, char **av, t_data *data);

#endif