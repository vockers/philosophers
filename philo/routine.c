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
	pthread_mutex_lock(&(philo->data->start_lock));
	pthread_mutex_unlock(&(philo->data->start_lock));
	philo->ate_time = get_time();
	if (philo->id % 2 == 1)
		usleep(100000);
	while (1)
	{
		if (is_dead(philo))
			return (NULL);
		pthread_mutex_lock(philo->fork_r);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_l);
		print_message(philo, "has taken a fork");
		print_message(philo, "is eating");
		usleep(philo->data->time_to_eat * 1000);
		philo->ate_time = get_time();
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
		usleep(philo->data->time_to_sleep * 1000);
		print_message(philo, "is thinking");
	}
}
