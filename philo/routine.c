/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vockers <vockers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 13:15:56 by vockers       #+#    #+#                 */
/*   Updated: 2023/11/27 13:15:56 by vockers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		usleep(1000000);
	while (1)
	{
		pthread_mutex_lock(philo->fork_r);
		printf("%d %d has taken a fork\n", get_runtime(philo->data->start_time), philo->id);
		pthread_mutex_lock(philo->fork_l);
		printf("%d %d has taken a fork\n", get_runtime(philo->data->start_time), philo->id);
		printf("%d %d is eating\n", get_runtime(philo->data->start_time), philo->id);
		usleep(philo->data->time_to_eat * 1000);
		philo->ate_time = get_time();
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
		usleep(philo->data->time_to_sleep * 1000);
		printf("%d %d is thinking\n", get_runtime(philo->data->start_time), philo->id);
	}
}