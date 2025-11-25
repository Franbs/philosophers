/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:51:38 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/11/25 17:13:22 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <unistd.h>

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
	long			start_time;
	bool			is_dead;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	data_lock;
	pthread_mutex_t	write_lock;
}	t_data;

// utils.c
int		ft_atol(const char *nptr);
int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);
long	ft_get_time(void);
void	ft_usleep(long time);
// parser.c
int		ft_check_args(int ac, char **av);
void	ft_log(t_philo *philo, char *msg);
// data.c
t_data	*ft_init_data(int ac, char **av);
// philo.c
void	ft_init_philos(t_data *data);
void	ft_assign_forks(t_philo *philo, t_data *data);
void	ft_is_dead(t_data *data);
void	ft_ate_min(t_data *data);
// mutex.c
int		ft_init_mutex_forks(t_data *data);
void	ft_destroy_mutex_forks(t_data *data);
void	ft_destroy_mutex_all(t_data *data);

#endif
