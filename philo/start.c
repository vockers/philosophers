/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vockers <vockers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 13:18:31 by vockers       #+#    #+#                 */
/*   Updated: 2023/11/27 13:18:31 by vockers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	philos_start(t_data *data)
{
	int	i;

	pthread_mutex_lock(&(data->start_lock));
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_create(&(data->philos[i].thread), NULL, &philo_routine, &(data->philos[i])) != 0)
			return (0);
		data->philos[i].last_eaten = get_time();
		i++;
	}
	data->start_time = get_time();
	pthread_mutex_unlock(&(data->start_lock));
	monitor_philos(data);
	return (join_threads(data));
}
