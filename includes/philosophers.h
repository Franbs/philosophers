/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:51:38 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/11/17 19:54:11 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				meals_eaten;
	long			last_meal_time;
	t_data			*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

typedef struct s_data
{
	int				n_philos;
	long			time_to_eat;
	long			time_to_die;
	long			time_to_sleep;
	int				n_min_eat;
	bool			is_dead;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}	t_data;

// utils.c
int		ft_atol(const char *nptr);
int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);
// parser.c
int		ft_check_args(int ac, char **av);
// data.c
t_data	*ft_init_data(int ac, char **av);
// philo.c
void	ft_init_philos(t_data *data);
void	ft_assign_forks(t_philo *philo, t_data *data);

#endif
