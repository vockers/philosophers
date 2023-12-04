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

static void	eat(t_philo *philo)
{
	if (is_dead(philo))
		return ;
	print_message(philo, "is eating");
	pthread_mutex_lock(&(philo->lock));
	philo->num_eaten++;
	philo->last_eaten = get_time();
	pthread_mutex_unlock(&(philo->lock));
	ft_msleep(philo->data->time_to_eat);
}

static int	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (is_dead(philo))
		return (0);
	first_fork = philo->fork_l;
	second_fork = philo->fork_r;
	if (philo->id % 2 == 0)
	{
		first_fork = philo->fork_r;
		second_fork = philo->fork_l;
	}
	pthread_mutex_lock(first_fork);
	print_message(philo, "has taken a fork");
	if (philo->data->philo_count == 1)
	{
		pthread_mutex_unlock(first_fork);
		ft_msleep(philo->data->time_to_die);
		return (0);
	}
	pthread_mutex_lock(second_fork);
	print_message(philo, "has taken a fork");
	return (1);
}

static void	philo_routine(t_philo *philo)
{
	while (1)
	{
		if (is_dead(philo))
			return ;
		if (!take_forks(philo))
			return ;
		eat(philo);
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
		if (is_dead(philo))
			return ;
		print_message(philo, "is sleeping");
		ft_msleep(philo->data->time_to_sleep);
		if (is_dead(philo))
			return ;
		print_message(philo, "is thinking");
	}
}

void	*philo_start(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&(philo->data->start_lock));
	if (philo->data->start == false)
	{
		pthread_mutex_unlock(&(philo->data->start_lock));
		return (NULL);
	}
	pthread_mutex_unlock(&(philo->data->start_lock));
	philo_routine(philo);
	return (NULL);
}
