/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vockers <vockers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 13:12:04 by vockers       #+#    #+#                 */
/*   Updated: 2023/11/27 13:12:04 by vockers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	s_philo
{
	int				id;
	int				num_eaten;
	long			last_eaten;
	bool			alive;
	pthread_t		thread;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	lock;
	struct s_data	*data;
}	t_philo;

typedef struct	s_data
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				min_eat;
	long			start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	start_lock;
	pthread_mutex_t	print_lock;
}	t_data;

int		parse_args(t_data *data, int argc, char **argv);
int		init_data(t_data *data);
int		philos_start(t_data *data);
void	*philo_routine(void *arg);
void	monitor_philos(t_data *data);
bool	is_dead(t_philo *philo);
void	clean_up(t_data *data);
void	clean_up_forks(pthread_mutex_t *forks, int num);

/*
 * @brief Get the current time in miliseconds
 */
long	get_time(void);
int		get_runtime(long start_time);
void	ft_sleep(int todo);
void	print_message(t_philo *philo, const char *msg);
int		ft_atoi(const char *str);

#endif
