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

int	philos_start(t_data *data)
{
	int	i;

	data->start_time = get_time();
	i = 0;
	while (i < data->philo_count)
	{
		pthread_create(&(data->philos[i].thread), NULL, &philo_routine, &(data->philos[i]));
		i++;
	}
}