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
	if (philo->eating == false)
	{
		if (philo->alive == false)
		{
			pthread_mutex_unlock(&(philo->lock));
			return (1);
		}
		if (get_time() - philo->last_eaten > philo->data->time_to_die)
		{
			philo->alive = false;
			pthread_mutex_unlock(&(philo->lock));
			return (1);
		}
	}
	pthread_mutex_unlock(&(philo->lock));
	return (0);
}

void kill_philos(t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_count)
	{
		data->philos[i].last_eaten = 0;
		i++;
	}
}

int check_table(t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_count)
	{
		if (is_dead(&(data->philos[i])))
		{
			kill_philos(data);
			printf("%d %d has died\n", get_runtime(data->start_time), data->philos[i].id);
			exit(0);
		}
		i++;
	}
	return (1);
}

void monitor_philos(t_data *data)
{
	while (1)
	{
		if (!check_table(data))
			return;
	}
}