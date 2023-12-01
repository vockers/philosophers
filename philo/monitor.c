/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vockers <vockers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/28 12:20:45 by vockers       #+#    #+#                 */
/*   Updated: 2023/11/28 12:20:45 by vockers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&(philo->lock));
	if (philo->alive == false)
	{
		pthread_mutex_unlock(&(philo->lock));
		return (true);
	}
	if (get_time() - philo->last_eaten >= philo->data->time_to_die)
	{
		philo->alive = false;
		pthread_mutex_unlock(&(philo->lock));
		return (true);
	}
	pthread_mutex_unlock(&(philo->lock));
	return (false);
}

bool	is_done(t_philo *philo)
{
	pthread_mutex_lock(&(philo->lock));
	if (philo->num_eaten >= philo->data->min_eat)
	{
		pthread_mutex_unlock(&(philo->lock));
		return (true);
	}
	pthread_mutex_unlock(&(philo->lock));
	return (false);
}

void	kill_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&(data->philos[i].lock));
		data->philos[i].alive = false;
		pthread_mutex_unlock(&(data->philos[i].lock));
		i++;
	}
}

int	check_table(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (is_dead(&(data->philos[i])))
		{
			kill_philos(data);
			printf("%d %d has died\n", \
				get_runtime(data->start_time), data->philos[i].id);
			return (0);
		}
		i++;
	}
	return (1);
}

bool	check_table_done(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (!is_done(&(data->philos[i])))
			return (false);
		i++;
	}
	kill_philos(data);
	return (true);
}

void	monitor_philos(t_data *data)
{
	while (1)
	{
		if (!check_table(data))
			return ;
		if (data->min_eat > 0 && check_table_done(data))
			return ;
	}
}
