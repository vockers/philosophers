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

static void	join_threads(t_data *data, int i)
{
	if (i != data->philo_count)
		pthread_mutex_unlock(&(data->start_lock));
	while (i-- > 0)
		pthread_join(data->philos[i].thread, NULL);
}

int	philos_start(t_data *data)
{
	int	i;

	pthread_mutex_lock(&(data->start_lock));
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_create(&(data->philos[i].thread), \
			NULL, &philo_start, &(data->philos[i])) != 0)
			return (join_threads(data, i), 0);
		i++;
	}
	data->start_time = get_time();
	while (i > 0)
	{
		i--;
		data->philos[i].last_eaten = data->start_time;
	}
	data->start = true;
	pthread_mutex_unlock(&(data->start_lock));
	monitor_philos(data);
	join_threads(data, data->philo_count);
	return (1);
}
