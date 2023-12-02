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

static void	kill_all(t_data *data)
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

static bool	is_everyone_alive(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (is_dead(&(data->philos[i])))
		{
			kill_all(data);
			printf("%d %d has died\n", \
				get_runtime(data->start_time), data->philos[i].id);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	is_everyone_done(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&(data->philos[i].lock));
		if (data->philos[i].num_eaten < data->min_eat)
		{
			pthread_mutex_unlock(&(data->philos[i].lock));
			return (false);
		}
		pthread_mutex_unlock(&(data->philos[i].lock));
		i++;
	}
	kill_all(data);
	return (true);
}

void	monitor_philos(t_data *data)
{
	while (1)
	{
		if (!is_everyone_alive(data))
			return ;
		if (data->min_eat > 0 && is_everyone_done(data))
			return ;
	}
}
