/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vockers <vockers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/01 14:05:09 by vockers       #+#    #+#                 */
/*   Updated: 2023/12/01 14:05:09 by vockers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_up(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&(data->start_lock));
	pthread_mutex_destroy(&(data->print_lock));
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&(data->philos[i].lock));
		pthread_mutex_destroy(&(data->forks[i]));
		i++;
	}
	free(data->forks);
	free(data->philos);
}