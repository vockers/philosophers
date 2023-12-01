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

void	eat(t_philo *philo)
{
	if (is_dead(philo))
		return ;
	print_message(philo, "is eating");
	pthread_mutex_lock(&(philo->lock));
	philo->num_eaten++;
	philo->last_eaten = get_time();
	pthread_mutex_unlock(&(philo->lock));
	ft_sleep(philo->data->time_to_eat);
}

int	take_forks(t_philo *philo)
{
	if (is_dead(philo))
		return (0);
	pthread_mutex_lock(philo->fork_r);
	print_message(philo, "has taken a fork");
	if (philo->data->philo_count == 1)
	{
		pthread_mutex_unlock(philo->fork_r);
		ft_sleep(philo->data->time_to_die);
		return (0);
	}
	pthread_mutex_lock(philo->fork_l);
	print_message(philo, "has taken a fork");
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&(philo->data->start_lock));
	pthread_mutex_unlock(&(philo->data->start_lock));
	philo->last_eaten = philo->data->start_time;
	if (philo->id % 2 == 0)
		ft_sleep(10);
	while (1)
	{
		if (is_dead(philo))
			return (NULL);
		if (!take_forks(philo))
			return (NULL);
		eat(philo);
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
		if (is_dead(philo))
			return (NULL);
		print_message(philo, "is sleeping");
		ft_sleep(philo->data->time_to_sleep);
		if (is_dead(philo))
			return (NULL);
		print_message(philo, "is thinking");
	}
}
